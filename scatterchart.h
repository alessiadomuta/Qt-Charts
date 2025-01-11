#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include "scattermodel.h"

class scatterchart: public baseChart{
private:
    scattermodel* model;
    void Draw();
    void Clear();
    void Redraw ();
public:
    scatterchart();
    virtual bool ImportFromFile(const QString&);
    virtual bool SaveFile(const QString &);
    QChart::QScatterSeries* getScatterSeries() const;
    virtual void AddtoChart(const QStringList&);
    virtual bool RemovefromChart(const QStringList&);
};

#endif // SCATTERCHART_H
