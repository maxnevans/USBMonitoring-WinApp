#pragma once
#include <stdio.h>
#include <stdint.h>
#include "IDeviceConnector.h"

#define DEFAULT_IP		"192.168.1.41"
#define DEFAULT_PORT	"32269"

class ConnectionProto
{
public:
	ConnectionProto();
	ConnectionProto(ConnectionProto&) = delete;
	~ConnectionProto();
	int GetVoltage();
	int GetAmperage();

private:
	IDeviceConnector* const connector;
};
