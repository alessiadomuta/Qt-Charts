#ifndef PIECHART_H
#define PIECHART_H

#include "piemodel.h"

class piechart:public baseChart{
private:
    piemodel* model;
    void Draw();
    void Clear();

public:
    piechart();
    virtual bool ImportFromFile(const QString&) override;
    virtual bool SaveFile(const QString &) override;
    QChart::QPieSeries* getPieSeries() const;
    virtual void AddtoChart(const QStringList&) override;
    virtual bool RemovefromChart(const QStringList&) override;
};

#endif // PIECHART_H
