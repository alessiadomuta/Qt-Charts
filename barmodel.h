#ifndef BARMODEL_H
#define BARMODEL_H

#include "linechart.h"
class barmodel{
private:
    QBarCategoryAxis* CAxis;
    QList<QBarSet*>* BSets;
    QBarSeries* BSeries;
    unsigned int FindMakeCategory(const QString& cat);
    unsigned int FindMakeBarSet(const QString& bar);
    int FindCategory(const QString & cat) const;
    int FindBarSet(const QString & bar) const;
    bool RemoveEmptyCategory(unsigned int);
    bool RemoveEmptyBarSet(unsigned int);
public:
    barmodel();
    QList<QBarSet*>* BarSets() const;
    QBarSeries* BarSeries() const;
    QBarCategoryAxis* CategoryAxis() const;
    virtual bool ImportFromFile(const QString& FileName);
    virtual bool SaveFile(const QString &FileName);
    virtual void AddtoModel(const QStringList& SL);
    virtual bool RemovefromModel(const QStringList& SL);
};

#endif // BARMODEL_H
