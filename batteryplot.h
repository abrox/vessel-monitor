#ifndef BATTERYPLOT_H
#define BATTERYPLOT_H

#include <qwt_plot.h>

const int HISTORY= 3600;
class BatteryPlot : public QwtPlot
{
    Q_OBJECT
public:
    BatteryPlot(QWidget *parent=NULL);
    ~BatteryPlot();
    void handleOneSecTimer( double curVal,double voltVal);

private:
    double timeData[HISTORY];

};

#endif // BATTERYPLOT_H
