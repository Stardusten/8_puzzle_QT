#include "eight_puzzle.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eight_puzzle w;
    w.show();
    return a.exec();
}
