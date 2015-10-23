#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
//#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m_window;
    m_window.show();
    return a.exec();
}
