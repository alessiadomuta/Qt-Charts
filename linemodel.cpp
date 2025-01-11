#include "linemodel.h"

linemodel::linemodel():LineSeries(new QLineSeries()){

}

QLineSeries* linemodel::GetLineSeries() const {return LineSeries;}

bool linemodel::ImportFromFile(const QString& FileName){
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
            if(i>0 && LineSeries->at(i-1).x()>x)
                CorrectInput=false;
            ++i;
            LineSeries->append(x,y);
        }
        if(!CorrectInput) {LineSeries->clear(); return false;}
        else{return true;}
    }
}

bool linemodel::SaveFile(const QString &FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "errore apertura file!";
        return false;
    }
    else{
        file.resize(0);
        QTextStream stream(&file);
        QList<QPointF> v=LineSeries->points();
        for(QList<QPointF>::const_iterator cit=v.begin();cit!=v.end();++cit){
            stream << cit->x() << ',' << cit->y() << '\n';
        }
        return true;
    }
}

void linemodel::AddtoChart(const QStringList& SList){
    qreal x=SList.first().toDouble();
    qreal y=SList.last().toDouble();
    unsigned int i=0;
    LineSeries->insert(i,QPointF(x,y));
}

bool linemodel::RemovefromChart(const QStringList& SL){
    qreal x=SL.first().toDouble();
    qreal y=SL.last().toDouble();
    bool found=false;
    for(unsigned int i=0; i<LineSeries->count() && !found;++i){
        if(LineSeries->at(i).x()==x && LineSeries->at(i).y()==y){
            LineSeries->removePoints(i,1);
            found=true;
        }
    }
    return found;
}




