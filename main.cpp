#include "mainwindow.h"
#include "startview.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    startview* startView = new startview();

    startView->show();

    return a.exec();

}
