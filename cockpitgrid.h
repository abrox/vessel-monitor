#ifndef COCKPITGRID_H
#define COCKPITGRID_H


#include <qframe.h>
#include <qpalette.h>

class QwtDial;
class VoltageMeter;

class CockpitGrid: public QFrame
{
    Q_OBJECT

public:
    CockpitGrid( QWidget *parent = NULL );

public Q_SLOTS:
    void batteryVoltageUpdated( double val );


private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( int pos );

    VoltageMeter *d_voltage;
};

#endif // COCKPITGRID_H
