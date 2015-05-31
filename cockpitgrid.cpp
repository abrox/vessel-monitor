#include "cockpitgrid.h"

#include <qlayout.h>
#include <qtimer.h>
#include <qwt_round_scale_draw.h>
#include "voltagemeter.h"
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
            d_voltage->setScaleStepSize( 20.0 );
            d_voltage->setScale( -120.0, 120.0 );
            d_voltage->scaleDraw()->setPenWidth( 2 );

            QTimer *timer = new QTimer( d_voltage );
            timer->connect( timer, SIGNAL( timeout() ),
                this, SLOT( changeSpeed() ) );
            timer->start( 50 );

            dial = d_voltage;
            break;
        }
        case 1:
        {
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

void CockpitGrid::changeSpeed()
{
    static double offset = 0.8;

    double speed = d_voltage->value();

    if ( ( speed < -110.0 && offset < 0.0 ) ||
        ( speed > 110.0 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    static int counter = 0;
    switch( counter++ % 12 )
    {
        case 0:
        case 2:
        case 7:
        case 8:
            break;
        default:
            d_voltage->setValue( speed + offset );
    }
}




