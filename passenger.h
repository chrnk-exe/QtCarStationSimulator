#ifndef PASSENGER_H
#define PASSENGER_H

#include <QColor>
#include <QPointF>
//#include <cashbox.h>

enum pass_states {NEW, WAIT, GO_TO_CASHBOX, STAY_ON_CASHBOX, GO_TO_EXIT};

class Passenger
{
public:
    Passenger();
    pass_states pass_state = NEW;
    QColor color;
    QPointF pos;

    QPointF start_pos;
    QPointF end_pos;

//    Cashbox my_cashbox;
    std::pair<int, int> my_cashbox_index;
    QList<bool> required_kits;
    int pos_count_start;
    int pos_count_end;

    bool operator== (const Passenger p) const
    {
        return this == &p;
    }
};

#endif // PASSENGER_H
