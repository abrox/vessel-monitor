#include "cockpitgrid.h"

#include <qlayout.h>
#include <qtimer.h>
#include <qlabel.h>
#include <qwt_round_scale_draw.h>

#include "voltagemeter.h"
#include "currentmeter.h"
#include "cockpitgrid.h"
#include "const.h"
#include "utils.h"

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
        QLabel *lb    = createLabel( i );

        layout->addWidget( dial, 0, i );
        layout->addWidget( lb, 1, i );
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
            d_voltage->setScale(VOLT_MIN, VOLT_MAX );
            d_voltage->scaleDraw()->setPenWidth( 2 );

            dial = d_voltage;
            break;
        }
        case 1:
        {
            d_current = new CurrentMeter( this );
            d_current->setScaleStepSize( 1.5 );
            d_current->setScale( CUR_MIN, CUR_MAX);
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

QLabel *CockpitGrid::createLabel( int pos )
{
    QLabel *lb=NULL;

    switch( pos )
    {
        case 0:
        {
            l_voltage = new QLabel("--\n" );
            lb = l_voltage;
            break;
        }
        case 1:
        {
            l_current = new QLabel( "--\n" );
            lb = l_current;
            break;
        }

    }

    if( lb )
    {

        QPalette palette;

        //white text
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        //set white text
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

        //set palette
        lb->setPalette(palette);

        //set font
        QFont font;
        font.setPointSize(12);

        lb->setFont(font);

        lb->setAlignment(Qt::AlignCenter);
    }
    return lb;
}

void CockpitGrid::batteryVoltageUpdated( double val )
{
    d_voltage->setValue( val );
    l_voltage->setText(QString().sprintf("%0.2f V\n",val));
}
void CockpitGrid::batteryCurrentUpdated( double val )
{
    d_current->setValue( val );
    l_current->setText(QString().sprintf("%0.4f A\n",val));
}


