#pragma once
#include "ConnectionProto.h"
#include <list>

class AppModel {
public:
	AppModel(size_t AVGPrecision);
	void RetrieveData();
	int GetUVoltage();
	int GetUAmperage();

private:
	int CalculateAVG(std::list<int>* uQueue);

private:
	ConnectionProto *cntProto;

	std::list<int> uVoltageQueue;
	std::list<int> uAmperageQueue;
	int uVoltage;
	int uAmperage;

	size_t AVGPrecision;
};

