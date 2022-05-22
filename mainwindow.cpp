#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(Canvas *canvas, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->canvas = canvas;
    ui->setupUi(this);

    ui->spinBox_2->setValue(canvas->s->GO_TO_CASHBOX_SPEED);
    ui->spinBox_3->setValue(canvas->s->GO_TO_EXIT_SPEED);
    ui->spinBox_4->setValue(canvas->s->SERVICE_TIME);
    ui->spinBox_7->setValue(canvas->s->N1);
    ui->spinBox_8->setValue(canvas->s->APPEAR_TIME);
    ui->spinBox_9->setValue(canvas->s->N2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    canvas->s->GO_TO_CASHBOX_SPEED = arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    canvas->s->GO_TO_EXIT_SPEED = arg1;
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    canvas->s->SERVICE_TIME = arg1;
}

void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    cout << "cashbox list1 size start: " << canvas->s->cashboxes_list[0].size() << endl;
    if (arg1 > canvas->s->N1)
    {
        for(int i = 0; i < arg1 - canvas->s->N1; i++)
        {
            Cashbox cashbox(QPointF(100, 100));
            canvas->s->cashboxes_list[0].append(cashbox);
        }

        canvas->s->N1 = arg1;
        QList<QPointF> cashbox_poses = canvas->s->get_cashbox_poses(0);
        cout << "cashbox poses length: " << cashbox_poses.size() << endl << "cashboxes list1 size: " << canvas->s->cashboxes_list1.size() << endl;
        for(int i = 0; i < canvas->s->cashboxes_list[0].size(); i++)
        {
            canvas->s->cashboxes_list[0][i].position = cashbox_poses[i];
        }
    }
    else if (arg1 < canvas->s->N1)
    {
        for(int i = 0; i < canvas->s->N1 - arg1; i++)
        {
//            Cashbox* cashbox = canvas->s->cashboxes_list[canvas->s->cashboxes_list.size() - 1];
            for(int j = 0; j < canvas->s->cashboxes_list[0][i].passengers_list.size(); j++)
            {
                canvas->s->cashboxes_list[0][i].passengers_list[j]->pass_state = GO_TO_EXIT;
                canvas->s->cashboxes_list[0][i].passengers_list[j]->start_pos = canvas->s->cashboxes_list[0][i].passengers_list[j]->pos;
                canvas->s->cashboxes_list[0][i].passengers_list[j]->end_pos = exit_pos;
                canvas->s->cashboxes_list[0][i].passengers_list[j]->pos_count_start = canvas->s->counter;
                canvas->s->cashboxes_list[0][i].passengers_list[j]->pos_count_end = canvas->s->counter +
                canvas->s->get_frames_count(canvas->s->cashboxes_list[0][i].passengers_list[j], canvas->s->GO_TO_EXIT_SPEED, canvas->s->RANDOM_OFFSET);
            }

            for(int j = 0; j < canvas->s->all_passengers.size(); j++)
            {
                canvas->s->all_passengers[j]->my_cashbox_index.second -= 1;
            }
            canvas->s->cashboxes_list[0].erase(canvas->s->cashboxes_list[0].begin());
        }
        canvas->s->N1 = arg1;
        QList<QPointF> cashbox_poses = canvas->s->get_cashbox_poses(0);
        for(int i = 0; i < canvas->s->cashboxes_list[0].size(); i++)
        {
            canvas->s->cashboxes_list[0][i].position = cashbox_poses[i];
        }
    }
    cout << "cashbox list1 size finish: " << canvas->s->cashboxes_list[0].size() << endl;
}

void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    canvas->s->APPEAR_TIME = arg1;
}

void MainWindow::on_spinBox_9_valueChanged(int arg1)
{
    Model* m = canvas->s;
    if (arg1 > m->N2)
    {
        for(int i = 0; i < arg1 - m->N2; i++)
        {
            Cashbox cashbox(QPointF(100, 100));
            m->cashboxes_list[1].append(cashbox);
        }

        m->N2 = arg1;
        QList<QPointF> cashbox_poses = m->get_cashbox_poses(1);

        for(int i = 0; i < m->cashboxes_list[1].size(); i++)
        {
            m->cashboxes_list[1][i].position = cashbox_poses[i];
        }
    }
    else if (arg1 < m->N2)
    {
        for(int i = 0; i < m->N2 - arg1; i++)
        {
//            Cashbox* cashbox = canvas->s->cashboxes_list[canvas->s->cashboxes_list.size() - 1];
            for(int j = 0; j < m->cashboxes_list[1][i].passengers_list.size(); j++)
            {
                m->cashboxes_list[1][i].passengers_list[j]->pass_state = GO_TO_EXIT;
                m->cashboxes_list[1][i].passengers_list[j]->start_pos = m->cashboxes_list[1][i].passengers_list[j]->pos;
                m->cashboxes_list[1][i].passengers_list[j]->end_pos = exit_pos;
                m->cashboxes_list[1][i].passengers_list[j]->pos_count_start = m->counter;
                m->cashboxes_list[1][i].passengers_list[j]->pos_count_end = m->counter +
                    m->get_frames_count(m->cashboxes_list[1][i].passengers_list[j], m->GO_TO_EXIT_SPEED, m->RANDOM_OFFSET);
            }

            for(int j = 0; j < m->all_passengers.size(); j++)
            {
                m->all_passengers[j]->my_cashbox_index.second -= 1;
            }
            m->cashboxes_list[1].erase(m->cashboxes_list[1].begin());
        }
        m->N2 = arg1;
        QList<QPointF> cashbox_poses = m->get_cashbox_poses(1);

        for(int i = 0; i < m->cashboxes_list[1].size(); i++)
        {
            m->cashboxes_list[1][i].position = cashbox_poses[i];
        }
    }
}

