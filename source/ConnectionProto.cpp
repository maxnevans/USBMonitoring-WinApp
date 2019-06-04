#include "ConnectionProto.h"
#include "WirelessConnector.h"

ConnectionProto::ConnectionProto()
	:
	connector(new WirelessConnector(DEFAULT_IP, DEFAULT_PORT))
{
}


ConnectionProto::~ConnectionProto()
{
	delete this->connector;
}

int ConnectionProto::GetVoltage()
{
	return this->connector->GetVoltage();
}

int ConnectionProto::GetAmperage()
{
	return this->connector->GetAmperage();
}