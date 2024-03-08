#include "startwindow.h"
#include <QApplication>
QString gd_pnum;
QString gp_dnum;
QString gs_dnum;
QString gs_pnum;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    w.show();
    return a.exec();
}
