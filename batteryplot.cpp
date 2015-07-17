#include "batteryplot.h"

#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_canvas.h>

#include "const.h"

BatteryPlot::BatteryPlot(QWidget *parent):QwtPlot( parent )
{

    //plot.setCanvasBackground( Qt::white );
    setAxisScale( QwtPlot::yLeft, VOLT_MIN, VOLT_MAX );
    setAxisScale( QwtPlot::yRight, CUR_MIN, CUR_MAX );
    enableAxis(QwtPlot::yRight,true);
    setAxisTitle(QwtPlot::yLeft,"Volt");
    setAxisTitle(QwtPlot::yRight,"Amp");
    insertLegend( new QwtLegend() );


    setAxisScale( QwtPlot::xBottom, 0, HISTORY );

    for ( int i = 0; i < HISTORY; i++ )
        timeData[HISTORY - 1 - i] = i;

}

BatteryPlot::~BatteryPlot()
{

}

