#ifndef USERINPUTS_H
#define USERINPUTS_H

#include <QObject>
#include <QDockWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>

#include "scatterchart.h"

enum chartTypes{pie, line, bar, spline, scatter};
class userinputs : public QGroupBox{

    Q_OBJECT

private:

    QLineEdit* firstData;
    QLineEdit* secondData;
    QLineEdit* thirdData;
    chartTypes tipo;

public:

    userinputs(chartTypes, QWidget* p =nullptr);
    QStringList getData() const;
    chartTypes getTipo() const;

signals:

    void insertData();
    void removeData();

};

#endif // USERINPUTS_H
