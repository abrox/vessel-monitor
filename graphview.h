#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <qframe.h>

class GraphView : public QFrame
{
    Q_OBJECT
public:
    GraphView(QWidget *parent=NULL);
    ~GraphView();

public Q_SLOTS:
    void batteryVoltageUpdated( double val );
    void batteryCurrentUpdated( double val );

};

#endif // GRAPHVIEW_H
