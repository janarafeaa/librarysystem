#include "Librarydata.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadSampleData();

    Loginwindow w;
    w.show();

    return a.exec();
}