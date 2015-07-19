#ifndef COCKPITGRID_H
#define COCKPITGRID_H


#include <qframe.h>
#include <qpalette.h>
#include <qlabel.h>

class QwtDial;
class VoltageMeter;
class CurrentMeter;

class CockpitGrid: public QFrame
{
    Q_OBJECT

public:
    CockpitGrid( QWidget *parent = NULL );

public Q_SLOTS:
    void batteryVoltageUpdated( double val );
    void batteryCurrentUpdated( double val );

private:
    QwtDial *createDial( int pos );
    QLabel *createLabel( int pos );

    VoltageMeter *d_voltage;
    CurrentMeter *d_current;

    QLabel *l_voltage;
    QLabel *l_current;
};

#endif // COCKPITGRID_H
