#include <qapplication.h>
#include <qtabwidget.h>
#include "cockpitgrid.h"
#include "batterydata.h"


int main ( int argc, char **argv )
{
    QApplication a( argc, argv );
    BatteryData bd;
    bd.connectToMqttServer();
    bd.subscribeFromMqttServer("jukka/#");
    QTabWidget tabWidget;
    tabWidget.addTab( new CockpitGrid, "Cockpit" );

    tabWidget.show();

    return a.exec();
}
