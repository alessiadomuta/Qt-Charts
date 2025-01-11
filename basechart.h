#ifndef BASECHART_H
#define BASECHART_H

#include <QtWidgets>
#include <QChart>
#include <QFile>
#include <QDebug>
#include <QString>


class baseChart : public QChart::QChart{
protected:
    QString savedFileName;
    QChart::QChartView* chartView;
public:
    QChart::QChartView* getChartView() const;
    QString getSavedFileName() const;
    virtual ~baseChart();
    virtual bool ImportFromFile(const QString&)=0;
    virtual bool SaveFile(const QString &)=0;
    virtual void AddtoChart(const QStringList&)=0;
    virtual bool RemovefromChart(const QStringList&)=0;
};

#endif // BASECHART_H
