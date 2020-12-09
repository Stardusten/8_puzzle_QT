#include "eight_puzzle.h"
#include "a_star_graph.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap("/Users/stardust/8_puzzle/Launch.png");
    pixmap = pixmap.scaled(700, 700, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QSplashScreen splash(pixmap);
    splash.show();

    eight_puzzle w;
    w.show();
    //splash.finish(&w);

    return a.exec();
}
