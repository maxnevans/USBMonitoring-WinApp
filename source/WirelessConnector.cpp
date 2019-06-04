#include "WirelessConnector.h"
#include "Exception.h"
#include <vector>

WirelessConnector::WirelessConnector(std::string ip, std::string port)
{
	this->voltageNonTS = 0;
	this->amperageNonTS = 0;

	WSADATA wsaData;
	this->socket = INVALID_SOCKET;
	addrinfo* result = NULL;
	addrinfo hints;
	int iResult;

	
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
		throw Exception(L"failed to initialize winsock library");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	
	iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0)
	{
		WSACleanup();
		throw Exception(L"getaddrinfo failed with error: " + iResult);
	}

	this->socket = ::socket(result->ai_family, result->ai_socktype,	result->ai_protocol);
	if (this->socket == INVALID_SOCKET) {
		WSACleanup();
		throw Exception(L"socket failed with error: " + WSAGetLastError());
	}

	iResult = connect(this->socket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(this->socket);
		this->socket = INVALID_SOCKET;
		throw Exception(L"fail to connect to specified server");
	}

	freeaddrinfo(result);

	this->hMutex = CreateMutex(NULL, FALSE, NULL);
	if (this->hThreadReciever == INVALID_HANDLE_VALUE)
		throw Exception(L"failed to create reciever mutex");

	this->hThreadReciever = CreateThread(NULL, 0, WirelessConnector::ThreadProcedure, this, 0, NULL);
	if (this->hThreadReciever == INVALID_HANDLE_VALUE)
		throw Exception(L"failed to create reciever thread");
}

WirelessConnector::~WirelessConnector()
{
	TerminateThread(this->hThreadReciever, 0);

	CloseHandle(this->hThreadReciever);
	CloseHandle(this->hMutex);

	closesocket(this->socket);
	WSACleanup();
}

void WirelessConnector::SendPacket(UARTPacket packet)
{	
	int iResult = send(this->socket, reinterpret_cast<char*>(&packet.id), sizeof(packet.id), 0);
	if (iResult == SOCKET_ERROR) {
		closesocket(this->socket);
		WSACleanup();
		throw Exception(L"send packet.id failed with error: " + WSAGetLastError());
	}
	iResult = send(this->socket, reinterpret_cast<char*>(&packet.data), sizeof(packet.data), 0);
	if (iResult == SOCKET_ERROR) {
		closesocket(this->socket);
		WSACleanup();
		throw Exception(L"send packet.data failed with error: " + WSAGetLastError());
	}
}

void WirelessConnector::SendPacket(uint16_t id, uint16_t data)
{
	UARTPacket packet;
	packet.id = id;
	packet.data = data;
	this->SendPacket(packet);
}

void WirelessConnector::RecievePacket(UARTPacket& packet)
{
	const int packSize = sizeof(packet.id) + sizeof(packet.data);
	uint8_t buffer[packSize];
	for (int j = 0; j < packSize; j++)
	{
		int iResult = recv(socket, reinterpret_cast<char*>(buffer + j), sizeof(uint8_t), 0);
		if (iResult == 0)
			throw Exception(L"connection has been closed by the server");
		else if (iResult != 1)
			throw Exception (L"recv failed with error: "  + WSAGetLastError() + L'\n');
	}

	packet.id = *reinterpret_cast<uint16_t*>(buffer);
	packet.data = *reinterpret_cast<uint16_t*>(buffer + 2);
}

DWORD WINAPI WirelessConnector::ThreadProcedure(_In_ LPVOID lpParameter)
{
	WirelessConnector* wc = reinterpret_cast<WirelessConnector*>(lpParameter);

	UARTPacket voltage;
	voltage.id = IDeviceConnector::UPID_VOLTAGE;
	voltage.data = 0;
	UARTPacket amperage;
	amperage.id = IDeviceConnector::UPID_AMPERAGE;
	amperage.data = 0;

	for (;;)
	{
		wc->SendPacket(voltage);
		wc->RecievePacket(voltage);
		wc->SendPacket(amperage);
		wc->RecievePacket(amperage);

		wc->ThreadCommunicator(voltage.data, amperage.data);
	}
	return 0;
}

void WirelessConnector::SetVoltageTS(int value)
{
	this->TakeMutex();
	this->voltageNonTS = value;
	this->ReleaseMutex();
}

void WirelessConnector::SetAmperageTS(int value)
{
	this->TakeMutex();
	this->voltageNonTS = value;
	this->ReleaseMutex();
}

int WirelessConnector::GetVoltageTS()
{
	int voltage = 0;
	this->TakeMutex();
	voltage = this->voltageNonTS;
	this->ReleaseMutex();
	return voltage;
}

int WirelessConnector::GetAmperageTS()
{
	int amperage = 0;
	this->TakeMutex();
	amperage = this->amperageNonTS;
	this->ReleaseMutex();
	return amperage;
}

void WirelessConnector::ReleaseMutex()
{
	if (!::ReleaseMutex(this->hMutex))
		throw Exception(L"unable to release mutex");
}

void WirelessConnector::TakeMutex()
{
	DWORD result;
	do
	{
		result = WaitForSingleObject(this->hMutex, INFINITE);
	}
	while (result == WAIT_TIMEOUT);

	switch (result)
	{
	case WAIT_ABANDONED:
		throw Exception(L"mutex has been abandoned");
		break;
	case WAIT_FAILED:
		throw Exception(L"mutex failed when tried to wait");
		break;
	}
}

void WirelessConnector::ThreadCommunicator(int voltageFromThread, int amperageFromThread)
{
	this->TakeMutex();
	this->voltageNonTS = voltageFromThread;
	this->amperageNonTS = amperageFromThread;
	this->ReleaseMutex();
}
