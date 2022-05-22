#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QPainter>
#include <model.h>

class Canvas: public QWidget
{
    Q_OBJECT
public:
    Canvas();
    Canvas(Model*, QWidget *parent = 0);
    QTimer _timer;
    Model* s;

public slots:
    void update_index();

protected:
    void paintEvent(QPaintEvent*);

};

#endif // CANVAS_H
