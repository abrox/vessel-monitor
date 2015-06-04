#include <qdebug.h>
#include "batterydata.h"
#include "utils.h"

const std::string voltTopic("battery/voltage");
const std::string currentTopic("battery/current");

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
        rc = subscribeFromMqttServer(voltTopic);
        rc = subscribeFromMqttServer(currentTopic);
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
    try{
        double val = stringToNumber<double>(data);

        if( topic == voltTopic )
            Q_EMIT updateBatteryVoltage(val);
        else
        if( topic ==  currentTopic )
            Q_EMIT updateBatteryCurrent(val);
        else
            qWarning("Unknown topic: %s",topic.c_str());

    }catch(std::runtime_error e){
        qWarning("Topic: %s invalid value: %s",topic.c_str(),e.what());
    }

    return 1;
}

void BatteryData::handleConnectionLost(char * cause)
{

}

