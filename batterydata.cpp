#include "batterydata.h"

BatteryData::BatteryData(QObject *parent) : QObject(parent),
                                            SimpleMqttClient("localhost","dummy")
{

}

BatteryData::~BatteryData()
{

}

