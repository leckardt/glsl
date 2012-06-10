#include <QtGui/QApplication>
#include "mainwindow.h"
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    #ifdef Q_WS_X11
    XInitThreads();
    #endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
