#ifndef BATTERYDATA_H
#define BATTERYDATA_H

#include <QObject>

#include "simplemqttclient.h"


class BatteryData : public QObject, public SimpleMqttClient
{
    Q_OBJECT


public:
    explicit BatteryData(QObject *parent = 0, const char* addr="localhost");
    ~BatteryData();
    int start();
    void stop();

    /// Overide from SimpleMqttClient.
    int handleStringMsgArrvd(std::string & topic,
                                     std::string & data
                                     );


    /// Overide from SimpleMqttClient.
    void handleConnectionLost(char * cause);

Q_SIGNALS:
            void updateBatteryVoltage(double val);
            void updateBatteryCurrent(double val);
};

#endif // BATTERYDATA_H
