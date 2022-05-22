#include <QApplication>
#include "canvas.h"
#include "mainwindow.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model m;
    Canvas canvas(&m);
    MainWindow w(&canvas);
    canvas.show();
    w.show();
    return a.exec();
}
