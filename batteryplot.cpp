#include "batteryplot.h"

#include <QTime>

#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_canvas.h>

#include "const.h"


class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw( const QTime &base ):
        baseTime( base )
    {
    }
    virtual QwtText label( double v ) const
    {
        QTime upTime = baseTime.addSecs( static_cast<int>( v ) );
        return upTime.toString();
    }
private:
    QTime baseTime;
};

BatteryPlot::BatteryPlot(QWidget *parent):
    QwtPlot( parent ),dataCount( 0 )
{


    setAutoReplot( false );

//    QwtPlotCanvas *canvas = new QwtPlotCanvas();
   // canvas->setBorderRadius( 10 );

    //setCanvas( canvas );

    plotLayout()->setAlignCanvasToScales( true );
    //plot.setCanvasBackground( Qt::white );
    setAxisScale( QwtPlot::yLeft, VOLT_MIN, VOLT_MAX );
    setAxisScale( QwtPlot::yRight, CUR_MIN, CUR_MAX );
    enableAxis(QwtPlot::yRight,true);
    setAxisTitle(QwtPlot::yLeft,"Volt");
    setAxisTitle(QwtPlot::yRight,"Amp");
    //setAxisTitle( QwtPlot::xBottom, " System Uptime [h:m:s]" );
    insertLegend( new QwtLegend() );


    setAxisScale( QwtPlot::xBottom, 0, HISTORY );

    setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
    setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    QwtScaleWidget *scaleWidget = axisWidget( QwtPlot::xBottom );
    const int fmh = QFontMetrics( scaleWidget->font() ).height();
    scaleWidget->setMinBorderDist( 0, fmh / 2 );

    setAxisScaleDraw( QwtPlot::xBottom,
        new TimeScaleDraw( QTime(QTime::currentTime()) ) );

    for ( int i = 0; i < HISTORY; i++ )
        timeData[HISTORY - 1 - i] = i;

    QwtPlotCurve *curve;

    curve = new QwtPlotCurve;
    curve->setTitle("volt");
    curve->setPen( Qt::red,2 );
    curve->attach( this );
    data[Voltage].curve = curve;

    curve = new QwtPlotCurve;
    curve->setTitle("Current");
    curve->setPen( Qt::blue,2 );
    curve->attach( this );
    data[Current].curve = curve;
    curve->setYAxis(QwtPlot::yRight);

}

BatteryPlot::~BatteryPlot()
{

}

void BatteryPlot::handleOneSecTimer( double curVal,double voltVal)
{
    for ( int i = dataCount; i > 0; i-- )
    {
        for ( int c = 0; c < NBatteryData; c++ )
        {
            if ( i < HISTORY )
                data[c].data[i] = data[c].data[i-1];
        }
    }

    data[Voltage].data[0] = 9;//voltVal;
    data[Current].data[0] = 4;//curVal;

    if ( dataCount < HISTORY )
        dataCount++;

    for ( int j = 0; j < HISTORY; j++ )
        timeData[j]++;

    setAxisScale( QwtPlot::xBottom,
        timeData[HISTORY - 1], timeData[0] );

    for ( int c = 0; c < NBatteryData; c++ )
    {
        data[c].curve->setRawSamples(
            timeData, data[c].data, dataCount );
    }

    replot();
}