#ifndef PIEMODEL_H
#define PIEMODEL_H

#include "basechart.h"

class piemodel{
private:
    QPieSeries* PieSeries;
public:
    piemodel();
    QPieSeries* getPieSeries() const;
    virtual bool ImportFromFile(const QString&);
    virtual bool SaveFile(const QString &);
    virtual void AddtoChart(const QStringList&);
    virtual bool RemovefromChart(const QStringList&);
};

#endif // PIEMODEL_H
