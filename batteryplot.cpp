#include "batteryplot.h"

#include <QTime>
#include <qdebug.h>
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
    QwtPlot( parent ),dataCount( 0 ),d_interval( 0.0, HISTORY )
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
    insertLegend( new QwtLegend(),QwtPlot::TopLegend);


    setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );

    setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
    setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    QwtScaleWidget *scaleWidget = axisWidget( QwtPlot::xBottom );
    const int fmh = QFontMetrics( scaleWidget->font() ).height();
    scaleWidget->setMinBorderDist( 0, fmh / 2 );

    setAxisScaleDraw( QwtPlot::xBottom,
        new TimeScaleDraw( QTime(QTime::currentTime()) ) );

    for ( int i = 0; i < HISTORY; i++ )
        timeData[i] = -abs(i);

    QwtPlotCurve *curve;

    curve = new QwtPlotCurve;
    curve->setTitle("volt");
    curve->setPen( Qt::red,1 );
    curve->attach( this );
    data[Voltage].curve = curve;

    curve = new QwtPlotCurve;
    curve->setTitle("Current");
    curve->setPen( Qt::blue,1 );
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

    data[Voltage].data[0] = voltVal;
    data[Current].data[0] = curVal;

    if ( dataCount < HISTORY )
        dataCount++;

    for ( int j = 0; j < HISTORY; j++ )
        timeData[j]++;

    setAxisScale( QwtPlot::xBottom,
        timeData[static_cast<int>(d_interval.maxValue() ) - 1], timeData[0] );

    for ( int c = 0; c < NBatteryData; c++ )
    {
        data[c].curve->setRawSamples(
            timeData, data[c].data, dataCount );
    }

    replot();
}

void BatteryPlot::setIntervalLength( double interval )
{
    qDebug() << "setIntervalLength" << interval;

    if ( interval > 0.0 && interval != d_interval.width() )
    {
        d_interval.setMaxValue( d_interval.minValue() + interval );
        setAxisScale( QwtPlot::xBottom,
            d_interval.minValue(), d_interval.maxValue() );

        replot();
    }
}
