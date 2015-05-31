#ifndef VOLTAGEMETER_H
#define VOLTAGEMETER_H


#include <qstring.h>
#include <qwt_dial.h>

class VoltageMeter: public QwtDial
{
public:
    VoltageMeter( QWidget *parent = NULL );

    void setLabel( const QString & );
    QString label() const;

protected:
    virtual void drawScaleContents( QPainter *painter,
        const QPointF &center, double radius ) const;

private:
    QString d_label;
};


#endif // VOLTAGEMETER_H
