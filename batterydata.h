#ifndef BATTERYDATA_H
#define BATTERYDATA_H
#include "simplemqttclient.h"
#include <QObject>


class BatteryData : public QObject, public SimpleMqttClient
{
    Q_OBJECT
public:
    explicit BatteryData(QObject *parent = 0, const char* addr="localhost");
    ~BatteryData();
    int start();
    void stop();

//signals:

//public slots:
};

#endif // BATTERYDATA_H
