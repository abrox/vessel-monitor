#ifndef BATTERYPLOT_H
#define BATTERYPLOT_H

#include <qwt_plot.h>
#include <qwt_interval.h>

#include "const.h"

class QwtPlotCurve;

class BatteryPlot : public QwtPlot
{
    Q_OBJECT

    enum BatteryData
    {
        Voltage=0,
        Current=1,
        NBatteryData
    };

public Q_SLOTS:
    void setIntervalLength( double );

public:
    BatteryPlot(QWidget *parent=NULL);
    ~BatteryPlot();
    void handleOneSecTimer( double curVal,double voltVal);

private:
    double timeData[HISTORY];
    struct
    {
        QwtPlotCurve *curve;
        double data[HISTORY];
    } data[NBatteryData];
    int dataCount;
    QwtInterval d_interval;

};

#endif // BATTERYPLOT_H
