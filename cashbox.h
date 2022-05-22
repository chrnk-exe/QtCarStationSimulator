#ifndef CASHBOX_H
#define CASHBOX_H

#include <QObject>
#include <QWidget>
#include <QPointF>

#include <passenger.h>

class Cashbox
{

public:
    Cashbox();
    Cashbox(QPointF pos);

    QList<Passenger*> passengers_list;
    QPointF position;
};

#endif // CASHBOX_H
