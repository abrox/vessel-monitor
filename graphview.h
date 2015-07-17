#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <qframe.h>

class BatteryPlot;

class GraphView : public QFrame
{
    Q_OBJECT
public:
    GraphView(QWidget *parent=NULL);
    ~GraphView();

public Q_SLOTS:
    void batteryVoltageUpdated( double val );
    void batteryCurrentUpdated( double val );

protected:
    void timerEvent( QTimerEvent *e );
private:
    BatteryPlot *plot;

};

#endif // GRAPHVIEW_H
