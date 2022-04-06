#include "mainwindow.h"
#include "mine.h"

#include <QApplication>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Mineswiper");

    w.show();
    return a.exec();
}
