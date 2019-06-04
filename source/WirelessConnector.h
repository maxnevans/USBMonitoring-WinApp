#pragma once
#include "IDeviceConnector.h"
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>


class WirelessConnector
	:
	public IDeviceConnector
{
public:
	WirelessConnector(std::string ip, std::string port);
	WirelessConnector(WirelessConnector&) = delete;
	~WirelessConnector();
	inline virtual int GetVoltage() override
	{
		return this->GetVoltageTS();
	}
	inline virtual int GetAmperage() override
	{
		return this->GetAmperageTS();
	}

private:
	void SendPacket(UARTPacket packet);
	void SendPacket(uint16_t id, uint16_t data);
	void RecievePacket(UARTPacket& packet);
	static DWORD WINAPI ThreadProcedure(_In_ LPVOID lpParameter);
	void SetVoltageTS(int value);
	void SetAmperageTS(int value);
	int GetVoltageTS();
	int GetAmperageTS();
	void ReleaseMutex();
	void TakeMutex();
	void ThreadCommunicator(int voltageFromThread, int amperageFromThread);

private:

	HANDLE hMutex;
	HANDLE hThreadReciever;
	SOCKET socket;
	int voltageNonTS;
	int amperageNonTS;
};

