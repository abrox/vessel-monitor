#ifndef BATTERYPLOT_H
#define BATTERYPLOT_H

#include <qwt_plot.h>

const int HISTORY= 60;

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

};

#endif // BATTERYPLOT_H
