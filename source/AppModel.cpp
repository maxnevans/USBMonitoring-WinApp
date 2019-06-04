#include "AppModel.h"

AppModel::AppModel(size_t AVGPrecision)
{
	this->cntProto = new ConnectionProto();
	this->uVoltage = 0;
	this->uAmperage = 0;
	this->AVGPrecision = AVGPrecision;
}

void AppModel::RetrieveData()
{
	int voltage = this->cntProto->GetVoltage();
	int amperage = this->cntProto->GetAmperage();
	this->uVoltageQueue.push_back(voltage);
	this->uAmperageQueue.push_back(amperage);
	if (this->uVoltageQueue.size() >= this->AVGPrecision)
		this->uVoltage = this->CalculateAVG(&this->uVoltageQueue);
	if (this->uAmperageQueue.size() >= this->AVGPrecision)
		this->uAmperage = this->CalculateAVG(&this->uAmperageQueue);
}

int AppModel::GetUVoltage()
{
	return this->uVoltage;
}

int AppModel::GetUAmperage()
{
	return this->uAmperage;
}

int AppModel::CalculateAVG(std::list<int> * uQueue)
{
	if (uQueue->size() < this->AVGPrecision)
		return 0;

	while (uQueue->size() > this->AVGPrecision)
		uQueue->pop_front();

	int avg = 0;
	for (int value : *uQueue)
		avg += value;

	avg /= static_cast<int>(this->AVGPrecision);
	return avg;
}