#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Loginwindow w;
    w.show();
    return QApplication::exec();
}
