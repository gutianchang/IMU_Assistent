#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    //return a.exec();

    QApplication * app = new QApplication(argc,argv);

    MainWindow w;

    w.show();

    int ret;

    ret  = app->exec();
    delete app;
    return ret;
}
