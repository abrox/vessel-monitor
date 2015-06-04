#include <qapplication.h>
#include <qtabwidget.h>
#include <qstring.h>
#include<stdexcept>

#include <syslog.h>

#include "cockpitgrid.h"
#include "batterydata.h"

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

    openlog("BatteryMonitor", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "%s",array.data());
    closelog();

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

        rc = bd.start();
        if( rc )
        {
            return -1;
        }

        QTabWidget tabWidget;
        tabWidget.addTab( new CockpitGrid, "Cockpit" );

        tabWidget.show();
        rc = a.exec();
        bd.stop();
    }catch(std::runtime_error e){
       qFatal("%s",e.what()) ;
    }
    return rc;

}
