#include "scattermodel.h"

scattermodel::scattermodel(): ScatterSeries(new QScatterSeries()){

}

QScatterSeries* scattermodel::getScatterSeries() const {return ScatterSeries;}

bool scattermodel::ImportFromFile(const QString& FileName){
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
            if(i>0 && ScatterSeries->at(i-1).x()>x)
                CorrectInput=false;
            ++i;
            ScatterSeries->append(x,y);
        }
        if(!CorrectInput) {ScatterSeries->clear(); return false;}
        else{return true;}
    }
}

bool scattermodel::SaveFile(const QString &FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "errore apertura file!";
        return false;
    }
    else{
        file.resize(0);
        QTextStream stream(&file);
        QList<QPointF> v=ScatterSeries->points();
        for(QList<QPointF>::const_iterator cit=v.begin();cit!=v.end();++cit){
            stream << cit->x() << ',' << cit->y() << '\n';
        }
        return true;
    }
}

void scattermodel::AddtoChart(const QStringList& SList){
    qreal x=SList.first().toDouble();
    qreal y=SList.last().toDouble();
    unsigned int i=0;
    //for( ;LineSeries->at(i).x()<x;++i){}
    ScatterSeries->insert(i,QPointF(x,y));
}

bool scattermodel::RemovefromChart(const QStringList& SL){
    qreal x=SL.first().toDouble();
    qreal y=SL.last().toDouble();
    bool found=false;
    for(unsigned int i=0; i<ScatterSeries->count() && !found;++i){
        if(ScatterSeries->at(i).x()==x && ScatterSeries->at(i).y()==y){
            ScatterSeries->removePoints(i,1);
            found=true;
        }
    }
    return found;
}
