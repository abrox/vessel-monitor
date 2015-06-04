#include <qdebug.h>
#include "batterydata.h"
#include "utils.h"

BatteryData::BatteryData(QObject *parent,const char* addr) : QObject(parent),
                                            SimpleMqttClient(addr,"dummy")
{

}

BatteryData::~BatteryData()
{

}

int BatteryData::start()
{
    int rc;

    rc = connectToMqttServer();

    if( !rc )
    {
        rc = subscribeFromMqttServer("battery/voltage");
        rc = subscribeFromMqttServer("battery/current");
    }
    else
       qCritical() <<"connect to mqtt server fails rc:" << rc;

    return rc;
}

void BatteryData::stop()
{

}


int BatteryData::handleStringMsgArrvd(std::string & topic, std::string & data)
{
    double val = stringToNumber<double>(data);

    Q_EMIT updateBatteryVoltage(val);

    return 1;
}

void BatteryData::handleConnectionLost(char * cause)
{
}

