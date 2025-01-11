#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QDockWidget>
#include <QObject>
#include <QButtonGroup>
#include <QList>
#include <QGroupBox>
#include <QMessageBox>

#include "basechart.h"
#include "userinputs.h"

class startview :public QMainWindow{

    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    baseChart* chart;
    userinputs* userIn;
    QWidget* userActions;
    QGroupBox* fileView;

public:

    startview();

    QLayout* createButtonsLayout();
    QLayout* createVerticalLayout();
    void createFileLayout();
    void userInput(chartTypes);

public slots:
    void openFile() const;
    void saveAsFile() const;
    void createPie();
    void createLine();
    void createBar();
    void createSpline();
    void createScatter();
    void addData();
    void deleteData();
};


#endif // STARTVIEW_H
