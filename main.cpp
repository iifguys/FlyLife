#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRect rect = QApplication::desktop()->screenGeometry(1);
    MainWindow w;
    w.show();
    w.initialize(rect);

    return a.exec();
}
