#include "graphview.h"
#include <qdebug.h>
#include <qlayout.h>
#include "const.h"
#include "utils.h"

#include "wheelbox.h"
#include "batteryplot.h"

GraphView::GraphView(QWidget *parent):
    QFrame( parent ),dVoltage(0),dCurrent(0)
{
    startTimer(1000);
    setAutoFillBackground( true );


    setPalette( colorTheme( QColor( Qt::darkGray ).dark( 150 ) ) );
    plot = new BatteryPlot;

    d_intervalWheel = new WheelBox( "Displayed [s]", 10.0, HISTORY, 10.0, this );
    d_intervalWheel->setValue( 60 );
    plot->setIntervalLength( d_intervalWheel->value() );

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 0);
    layout->setMargin(0);

    layout->addWidget(plot,0,0);
    layout->addWidget(d_intervalWheel,0,1);

    connect( d_intervalWheel, SIGNAL( valueChanged( double ) ),
        plot, SLOT( setIntervalLength( double ) ) );
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
    plot->handleOneSecTimer(dCurrent,dVoltage);
}
