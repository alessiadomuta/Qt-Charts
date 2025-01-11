#ifndef LINECHART_H
#define LINECHART_H

#include "linemodel.h"

class linechart:public baseChart{
private:
    linemodel* model;
    void Draw();
    void Clear();
    void Redraw();
public:
    linechart();
    virtual bool ImportFromFile(const QString&) override;
    virtual bool SaveFile(const QString &) override;
    QChart::QLineSeries* getLineSeries() const;
    virtual void AddtoChart(const QStringList&) override;
    virtual bool RemovefromChart(const QStringList&) override;
};

#endif // LINECHART_H
