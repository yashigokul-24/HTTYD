#include <QApplication>
#include "httyd_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    httyd_mainwindow w;
    w.show();
    return app.exec();
}
