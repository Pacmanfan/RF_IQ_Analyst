#include <QApplication>
#include "mainwindow.h"
#include <dirent.h>
#include <fstream>
#include <string>
#include <sstream>
#include <qcustomplot.h>

#define CLIENTNAME "wbtclient" // for detecting whether we're local or remote


using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE( icons );
    MainWindow w;
    w.show();

    return a.exec();
}

