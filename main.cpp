#include "mainwindow.h"
#include <vector>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    // test Grid::idvec
    std::vector<double> test1 = {0,1,2};

    std::cout << (test1 == test1) << std::endl; // marche pas encore

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
