#include "model.h"
#include "passenger.h"
#include <QPainter>
#include <QtGlobal>
#include <cstdlib>
#include <cashbox.h>
#include <iostream>

using namespace std;

Model::Model()
{

    QList<QPointF> cashbox_poses1 = get_cashbox_poses(0);
    for(QPointF pos : cashbox_poses1)
    {
        Cashbox cashbox(pos);
        cashboxes_list1.append(cashbox);
    }
    QList<QPointF> cashbox_poses2 = get_cashbox_poses(1);
    for(QPointF pos : cashbox_poses2)
    {
        Cashbox cashbox(pos);
        cashboxes_list2.append(cashbox);
    }

    cashboxes_list.append(cashboxes_list1);
    cashboxes_list.append(cashboxes_list2);
}

QList<QPointF> Model::get_cashbox_poses(int cashbox_type)
{
    QList<QPointF> final_list;
    if(cashbox_type == 0){
        int half = N1 / 2;
        int offset = (N1%2 != 0 ? 0 : 1);
        for(int i = 0; i < N1; i++)
        {
            final_list.append(QPointF(600, 300) + QPointF(0, 100) * (i - half) + offset * QPointF(0, 50));
        }
        return final_list;
    }
    else
    {
        int half = N2 / 2;
        int offset = (N2%2 != 0 ? 0 : 1);
        for(int i = 0; i < N2; i++)
        {
            final_list.append(QPointF(200, 300) + QPointF(0, 100) * (i - half) + offset * QPointF(0, 50));
        }
        return final_list;
    }
}

pair<int, int> Model::choose_cashbox(Passenger* p)
{
    for(int i = 0; i < 2; i++)
    {
        if(p->required_kits[i])
        {
            QList<int> cashbox_sizes;
            for(int k = 0; k < cashboxes_list[i].size(); k++) cashbox_sizes.append(cashboxes_list[i][k].passengers_list.size());
            int cashbox_index = min_element(cashbox_sizes.begin(), cashbox_sizes.end()) - cashbox_sizes.begin();

            if (cashboxes_list[i][cashbox_index].passengers_list.size() <= MAX_QUEUE_LENGTH)
            {

                p->required_kits[i] = false;
                return make_pair(i, cashbox_index);
            }
        }
    }
    return make_pair(-1, -1);
}

int Model::move()
{
    for(int i = 0; i < (int)all_passengers.size(); i++)
    {
        if (all_passengers[i]->pass_state == NEW )
        {
            pair<int, int> choosen_cashbox = choose_cashbox(all_passengers[i]);

            if (choosen_cashbox.first == -1)
            {
                all_passengers[i]->pass_state = GO_TO_EXIT;
                all_passengers[i]->start_pos = all_passengers[i]->pos;
                all_passengers[i]->end_pos = exit_pos;
                all_passengers[i]->pos_count_start = counter;
                all_passengers[i]->pos_count_end = counter + get_frames_count(all_passengers[i], GO_TO_EXIT_SPEED, RANDOM_OFFSET);
            }
            else
            {
                cashboxes_list[choosen_cashbox.first][choosen_cashbox.second].passengers_list.append(all_passengers[i]);
                all_passengers[i]->start_pos = all_passengers[i]->pos;
                all_passengers[i]->end_pos = QPointF(cashboxes_list[choosen_cashbox.first][choosen_cashbox.second].position);
                all_passengers[i]->pass_state = GO_TO_CASHBOX;
                all_passengers[i]->pos_count_start = counter;
                all_passengers[i]->pos_count_end = counter + get_frames_count(all_passengers[i], GO_TO_CASHBOX_SPEED, RANDOM_OFFSET);;
                all_passengers[i]->my_cashbox_index = choosen_cashbox;
            }
        }
        else if (all_passengers[i]->pass_state == GO_TO_CASHBOX)
        {
            if (all_passengers[i]->pos_count_end < counter)
            {
                all_passengers[i]->pass_state = STAY_ON_CASHBOX;
                all_passengers[i]->pos_count_end = counter + get_service_time();
            }
            else
            {
                all_passengers[i]->pos = get_path_point(all_passengers[i]);
            }
        }
        else if (all_passengers[i]->pass_state == STAY_ON_CASHBOX)
        {
            if (all_passengers[i]->pos_count_end < counter)
            {
                if(all_passengers[i]->my_cashbox_index.second > -1)
                cashboxes_list[all_passengers[i]->my_cashbox_index.first][all_passengers[i]->my_cashbox_index.second].passengers_list.clear();

                pair<int, int> choosen_cashbox = choose_cashbox(all_passengers[i]); 

                if (choosen_cashbox.first == -1 || cashboxes_list[choosen_cashbox.first][choosen_cashbox.second].passengers_list.size() > MAX_QUEUE_LENGTH)
                {
                    all_passengers[i]->pass_state = GO_TO_EXIT;
                    all_passengers[i]->start_pos = all_passengers[i]->pos;
                    all_passengers[i]->end_pos = exit_pos;
                    all_passengers[i]->pos_count_start = counter;
                    all_passengers[i]->pos_count_end = counter + get_frames_count(all_passengers[i], GO_TO_EXIT_SPEED, RANDOM_OFFSET);
                }
                else
                {
                    cashboxes_list[choosen_cashbox.first][choosen_cashbox.second].passengers_list.append(all_passengers[i]);
                    all_passengers[i]->start_pos = all_passengers[i]->pos;
                    all_passengers[i]->end_pos = QPointF(cashboxes_list[choosen_cashbox.first][choosen_cashbox.second].position);
                    all_passengers[i]->pass_state = GO_TO_CASHBOX;
                    all_passengers[i]->pos_count_start = counter;
                    all_passengers[i]->pos_count_end = counter + get_frames_count(all_passengers[i], GO_TO_CASHBOX_SPEED, RANDOM_OFFSET);;
                    all_passengers[i]->my_cashbox_index = choosen_cashbox;
                }
            }
            else
            {

            }
        }
        else if (all_passengers[i]->pass_state == GO_TO_EXIT)
        {
            if (all_passengers[i]->pos_count_end < counter)
            {
                all_passengers.erase(all_passengers.begin()+i);
                i -= 1;
            }
            else
            {
                all_passengers[i]->pos = get_path_point(all_passengers[i]);
            }
        }
    }
    counter += 1;

    if (counter % get_appearing_time() == 0)
    {
        Passenger* pass = new Passenger();
//        pass->color = QColor::fromHsl(rand()%359, 255, 127);

        pass->pos = QPointF(rand()%300 + 100, 50);

        all_passengers.append(pass);
    }
    return 0;
}

QPointF Model::get_path_point(Passenger *pass)
{
    float full_len = (pass->end_pos - pass->start_pos).manhattanLength();
    float lerp_count = (float)(counter - pass->pos_count_start) / (pass->pos_count_end - pass->pos_count_start);

    float part_len = full_len * lerp_count;
    QPointF final_pos = pass->start_pos + (pass->end_pos - pass->start_pos) * (part_len / full_len);

    return final_pos;
}

int Model::draw(QPainter* p)
{
    p->setPen(QPen(Qt::black));

    p->drawRect(50, 25, 400, 60);

    for(int i = 0; i < cashboxes_list.size(); i++)
    {
        for(int j = 0; j < cashboxes_list[i].size(); j++)
        {
            p->setBrush(QBrush(Qt::black));
            p->drawEllipse(cashboxes_list[i][j].position, 30, 30);
            p->setBrush(QBrush(Qt::white));
            p->drawEllipse(cashboxes_list[i][j].position, 29, 29);
        }
    }


    p->setBrush(QBrush(Qt::black));
    p->drawEllipse(exit_pos, 29, 29);

    for(Passenger *pass : all_passengers)
    {
        p->setBrush(QBrush(pass->color));
        p->drawEllipse(pass->pos, 25, 25);
    }
    return 0;
}

int Model::get_frames_count(Passenger* pass, int speed, float offset)
{
    float length = (pass->end_pos - pass->start_pos).manhattanLength();

    float offset_temp = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (offset * 2)));
    int result_frames = length / (speed * 2 - offset_temp);

    return (result_frames > 0 ? result_frames : 1);
}

int Model::get_service_time()
{
    int temp = SERVICE_TIME * 2 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (RANDOM_OFFSET * 2)));
    return  (temp > 0 ? temp : 0);
}

int Model::get_appearing_time()
{
    int temp = APPEAR_TIME * 2 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (RANDOM_OFFSET * 2)));
    return  (temp > 0 ? temp : 1);
}

