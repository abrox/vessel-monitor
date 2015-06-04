#include "cockpitgrid.h"

#include <qlayout.h>
#include <qtimer.h>
#include <qwt_round_scale_draw.h>
#include "voltagemeter.h"
#include "currentmeter.h"
#include "cockpitgrid.h"

CockpitGrid::CockpitGrid( QWidget *parent ):
    QFrame( parent )
{
    setAutoFillBackground( true );

    setPalette( colorTheme( QColor( Qt::darkGray ).dark( 150 ) ) );

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );

    int i;
    for ( i = 0; i < 2; i++ )
    {
        QwtDial *dial = createDial( i );
        layout->addWidget( dial, 0, i );
    }

    for ( i = 0; i < layout->columnCount(); i++ )
        layout->setColumnStretch( i, 1 );
}

QwtDial *CockpitGrid::createDial( int pos )
{
    QwtDial *dial = NULL;
    switch( pos )
    {
        case 0:
        {
            d_voltage = new VoltageMeter( this );
            d_voltage->setScaleStepSize( 2.0 );
            d_voltage->setScale( 8.0, 16.0 );
            d_voltage->scaleDraw()->setPenWidth( 2 );

            dial = d_voltage;
            break;
        }
        case 1:
        {
            d_current = new CurrentMeter( this );
            d_current->setScaleStepSize( 2.0 );
            d_current->setScale( -6.0, 6.0 );
            d_current->scaleDraw()->setPenWidth( 2 );

            dial = d_current;
            break;
        }

    }

    if ( dial )
    {
        dial->setReadOnly( true );
        dial->setLineWidth( 4 );
        dial->setFrameShadow( QwtDial::Sunken );
    }
    return dial;
}

QPalette CockpitGrid::colorTheme( const QColor &base ) const
{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.dark( 150 ) );
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Light, base.light( 170 ) );
    palette.setColor( QPalette::Dark, base.dark( 170 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    palette.setColor( QPalette::WindowText, base.dark( 200 ) );

    return palette;
}

void CockpitGrid::batteryVoltageUpdated( double val )
{
    d_voltage->setValue( val );
}
void CockpitGrid::batteryCurrentUpdated( double val )
{
    d_current->setValue( val );
}



