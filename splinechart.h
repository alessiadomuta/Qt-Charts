#ifndef SPLINECHART_H
#define SPLINECHART_H

#include "splinemodel.h"

class splinechart :public baseChart{
private:
    splinemodel* model;
    void Draw();
    void Clear();
    void Redraw();
public:
    splinechart();
    virtual bool ImportFromFile(const QString&) override;
    virtual bool SaveFile(const QString &) override;
    QSplineSeries* getSplineSeries() const;
    virtual void AddtoChart(const QStringList&) override;
    virtual bool RemovefromChart(const QStringList&) override;
};

#endif // SPLINECHART_H
