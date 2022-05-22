#include "canvas.h"
#include "Qt"

Canvas::Canvas() { }

Canvas::Canvas(Model* f, QWidget *parent) : QWidget(parent)
{
    s = f;
    setFixedSize(800,600);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(update_index()));
    _timer.start(10);
}

void Canvas::update_index()
{
    s->move();
    this->update();
}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p);
    p.end();
}
