#include <qapplication.h>
#include <qtabwidget.h>
#include <qstring.h>
#include <stdexcept>
#include <iostream>

#include <syslog.h>

#include "cockpitgrid.h"
#include "batterydata.h"
#include "graphview.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1 %2 %3").arg(msg).arg(context.file).arg(context.line);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1 %l").arg(msg);
    }

    QByteArray array = txt.toLocal8Bit();

    std::cout << array.data() << std::endl;
/*
    openlog("BatteryMonitor", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "%s",array.data());
    closelog();
*/
    if( type == QtFatalMsg )
        abort();
}


int main ( int argc, char **argv )
{
    QApplication a( argc, argv );
    qInstallMessageHandler(myMessageOutput);
    int rc =-1;
    try{
        BatteryData bd;
        QTabWidget  tabWidget;
        CockpitGrid *cp = new CockpitGrid;
        GraphView   *gv = new GraphView;

        QObject::connect(&bd, &BatteryData::updateBatteryVoltage,
                          cp, &CockpitGrid::batteryVoltageUpdated);
        QObject::connect(&bd, &BatteryData::updateBatteryVoltage,
                          gv, &GraphView::batteryVoltageUpdated);


        QObject::connect(&bd, &BatteryData::updateBatteryCurrent,
                          cp, &CockpitGrid::batteryCurrentUpdated);
        QObject::connect(&bd, &BatteryData::updateBatteryCurrent,
                          gv, &GraphView::batteryCurrentUpdated);

        tabWidget.addTab( cp, "Cockpit" );
        tabWidget.addTab( gv, "Graph" );

        rc = bd.start();
        if( rc )
        {
            return -1;
        }

        tabWidget.resize(640,400);
        tabWidget.show();
        rc = a.exec();
        bd.stop();
    }catch(std::runtime_error e){
       qFatal("%s",e.what()) ;
    }
    return rc;

}
