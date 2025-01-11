#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H

#include "barchart.h"

class splinemodel{
private:
    QSplineSeries* SplineSeries;
public:
    splinemodel();
    QSplineSeries* getSplineSeries() const;
    virtual bool ImportFromFile(const QString& FileName);
    virtual bool SaveFile(const QString &FileName);
    virtual void AddtoChart(const QStringList& SL);
    virtual bool RemovefromChart(const QStringList& SL);
};


#endif // SPLINEMODEL_H
