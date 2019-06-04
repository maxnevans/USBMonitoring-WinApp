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
	virtual int GetVoltage() override;
	virtual int GetAmperage() override;

private:
	void SendPacket(UARTPacket packet);
	void SendPacket(uint16_t id, uint16_t data);
	void RecievePacket(UARTPacket& packet);

private:

	SOCKET socket;
};

