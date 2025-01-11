#include "splinemodel.h"

splinemodel::splinemodel(): SplineSeries(new QSplineSeries()){

}

QSplineSeries* splinemodel::getSplineSeries() const {return SplineSeries;}

bool splinemodel::ImportFromFile(const QString& FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    else{
        bool CorrectInput=true;
        QString line;
        unsigned int i=0;
        qreal x;
        qreal y;
        while (!file.atEnd() && CorrectInput) {
            line=file.readLine();
            x=line.split(',').first().toDouble(&CorrectInput);
            y=line.split(',').last().toDouble(&CorrectInput);
            if(i>0 && SplineSeries->at(i-1).x()>x)
                CorrectInput=false;
            ++i;
            SplineSeries->append(x,y);
        }
        if(!CorrectInput) {SplineSeries->clear(); return false;}
        else{return true;}
    }
}

bool splinemodel::SaveFile(const QString &FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "errore apertura file!";
        return false;
    }
    else{
        file.resize(0);
        QTextStream stream(&file);
        QList<QPointF> v=SplineSeries->points();
        for(QList<QPointF>::const_iterator cit=v.begin();cit!=v.end();++cit){
            stream << cit->x() << ',' << cit->y() << '\n';
        }
        return true;
    }
}

void splinemodel::AddtoChart(const QStringList& SList){
    qreal x=SList.first().toDouble();
    qreal y=SList.last().toDouble();
    unsigned int i=0;
    //for( ;LineSeries->at(i).x()<x;++i){}
    SplineSeries->insert(i,QPointF(x,y));
}

bool splinemodel::RemovefromChart(const QStringList& SL){
    qreal x=SL.first().toDouble();
    qreal y=SL.last().toDouble();
    bool found=false;
    for(unsigned int i=0; i<SplineSeries->count() && !found;++i){
        if(SplineSeries->at(i).x()==x && SplineSeries->at(i).y()==y){
            SplineSeries->removePoints(i,1);
            found=true;
        }
    }
    return found;
}
