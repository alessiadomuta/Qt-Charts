#ifndef SCATTERMODEL_H
#define SCATTERMODEL_H

#include "splinechart.h"

class scattermodel{
private:
    QScatterSeries* ScatterSeries;
public:
    scattermodel();
    QScatterSeries* getScatterSeries() const;
    virtual bool ImportFromFile(const QString& FileName);
    virtual bool SaveFile(const QString &FileName);
    virtual void AddtoChart(const QStringList& SL);
    virtual bool RemovefromChart(const QStringList& SL);
};

#endif // SCATTERMODEL_H
