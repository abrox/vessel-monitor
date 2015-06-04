#ifndef CURRENTMETER_H
#define CURRENTMETER_H

#include <qstring.h>
#include <qwt_dial.h>

class CurrentMeter: public QwtDial
{
public:
    CurrentMeter( QWidget *parent = NULL );

    void setLabel( const QString & );
    QString label() const;

protected:
    virtual void drawScaleContents( QPainter *painter,
        const QPointF &center, double radius ) const;

private:
    QString d_label;
};


#endif // CURRENTMETER_H
