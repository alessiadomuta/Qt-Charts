#ifndef LINEMODEL_H
#define LINEMODEL_H

#include "piechart.h"

class linemodel{
private:
    QLineSeries* LineSeries;
public:
    linemodel();
    QLineSeries* GetLineSeries() const;
    virtual bool ImportFromFile(const QString& FileName);
    virtual bool SaveFile(const QString &FileName);
    virtual void AddtoChart(const QStringList& SL);
    virtual bool RemovefromChart(const QStringList& SL);
};

#endif // LINEMODEL_H
