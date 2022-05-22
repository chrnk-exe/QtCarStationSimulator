#include "passenger.h"

Passenger::Passenger()
{
    bool first = rand()%2 ? true : false;
    bool second = rand()%2 ? true : false;
    required_kits.append(first);
    required_kits.append(second);
    color = Qt::blue;
    if(first && second){
        color = Qt::green;
    } else {
        if(first) color = Qt::red;
        if(second) color = Qt::yellow;
    }
}



