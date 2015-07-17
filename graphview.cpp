#include "graphview.h"
#include <qdebug.h>
#include <qlayout.h>

#include "batteryplot.h"

GraphView::GraphView(QWidget *parent):
    QFrame( parent ),dVoltage(0),dCurrent(0)
{
    startTimer(1000);
    plot = new BatteryPlot;

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 5 );

    layout->addWidget(plot,0,0);

}

GraphView::~GraphView()
{

}

void GraphView::batteryVoltageUpdated( double val )
{
    dVoltage = val;
}
void GraphView::batteryCurrentUpdated( double val )
{
    dCurrent = val;
}

void GraphView::timerEvent( QTimerEvent * )
{
    qDebug("Timer");
    plot->handleOneSecTimer(dCurrent,dVoltage);
}
