#ifndef BATTERYPLOT_H
#define BATTERYPLOT_H

#include <qwt_plot.h>

const int HISTORY= 60;
class BatteryPlot : public QwtPlot
{
    Q_OBJECT
public:
    BatteryPlot(QWidget *parent=NULL);
    ~BatteryPlot();

private:
    double timeData[HISTORY];

};

#endif // BATTERYPLOT_H
