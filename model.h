#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
#include <passenger.h>
#include <cashbox.h>
#include <iostream>

using namespace std;

#define exit_pos QPointF(750, 50)


class Model
{
public:
    Model();
    int SERVICE_TIME = 20;
    int APPEAR_TIME = 20;

    int GO_TO_QUEUE_SPEED = 2;
    int GO_TO_CASHBOX_SPEED = 3;
    int GO_TO_EXIT_SPEED = 3;

    int RANDOM_OFFSET = 1;
    int MAX_QUEUE_LENGTH = 0;

    int N1 = 3;
    int N2 = 3;

    int get_frames_count(Passenger* pass, int speed, float offset);
    int get_service_time();
    int get_appearing_time();

    QList<QPointF> get_cashbox_poses(int cashbox_type);

    QList<Passenger*> all_passengers;
    QList<Cashbox> cashboxes_list1;
    QList<Cashbox> cashboxes_list2;

    QList<QList<Cashbox>> cashboxes_list;

    QPointF get_path_point(Passenger *pass);

    pair<int, int> choose_cashbox(Passenger*);

    int draw(QPainter* p);
    int move();
    int counter = 0;
};

#endif // MODEL_H
