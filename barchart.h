#ifndef BARCHART_H
#define BARCHART_H

#include "barmodel.h"

class barchart: public baseChart{
private:
    barmodel* model;
    void Draw();
    void Clear();
    void Redraw();
public:
    barchart();
    virtual bool ImportFromFile(const QString&) override;
    virtual bool SaveFile(const QString &) override;
    QChart::QBarSeries* getBarSeries() const;
    virtual void AddtoChart(const QStringList&) override;
    virtual bool RemovefromChart(const QStringList&) override;
};

#endif // BARCHART_H
