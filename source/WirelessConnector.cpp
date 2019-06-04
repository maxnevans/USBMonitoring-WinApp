#include "WirelessConnector.h"
#include "Exception.h"
#include <vector>

WirelessConnector::WirelessConnector(std::string ip, std::string port)
{
	WSADATA wsaData;
	this->socket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
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
}

WirelessConnector::~WirelessConnector()
{
	closesocket(this->socket);
	WSACleanup();
}

int WirelessConnector::GetVoltage()
{
	UARTPacket pack;
	pack.id = UPID_VOLTAGE;
	this->SendPacket(pack);
	this->RecievePacket(pack);
	return static_cast<uint16_t>(pack.data);
}

int WirelessConnector::GetAmperage()
{
	UARTPacket pack;
	pack.id = UPID_AMPERAGE;
	this->SendPacket(pack);
	this->RecievePacket(pack);
	return static_cast<uint16_t>(pack.data);
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
