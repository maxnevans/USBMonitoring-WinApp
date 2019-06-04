#pragma once
#include <stdint.h>

class IDeviceConnector
{
protected:
	struct UARTPacket
	{
		uint16_t id;
		uint16_t data;
	};
public:
	virtual int GetVoltage() = 0;
	virtual int GetAmperage() = 0;

protected:

	static constexpr const uint16_t UPID_NONE		= 0x0000;
	static constexpr const uint16_t UPID_INIT 		= 0x0001;
	static constexpr const uint16_t UPID_DEINIT 	= 0x0002;
	static constexpr const uint16_t UPID_VOLTAGE 	= 0x0003;
	static constexpr const uint16_t UPID_AMPERAGE 	= 0x0004;
	static constexpr const uint16_t UPID_SYNC		= 0x0005;
	static constexpr const uint16_t UPID_SYNC_START	= 0x0006;
	static constexpr const uint16_t UPID_SYNC_END	= 0x0007;
	static constexpr const uint16_t UPID_SYNC_ERROR	= 0x0008;
	static constexpr const uint16_t UPID_ERROR 		= 0x00FE;

	static constexpr const uint16_t UPDT_NONE		= 0x0000;
	static constexpr const uint16_t UPDT_5V1		= 0x0FFF;
	static constexpr const uint16_t UPDT_SUCCESS	= 0x0001;
	static constexpr const uint16_t UPDT_FAIL		= 0x0002;

};