#include <QtGui/QApplication>
#include "WorkStatus.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WorkStatus status;

    QObject::connect(&status, SIGNAL(quit()), &a, SLOT(quit()));

    return a.exec();
}
