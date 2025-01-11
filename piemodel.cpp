#include "piemodel.h"

piemodel::piemodel():PieSeries(new QPieSeries()){

}

QPieSeries* piemodel::getPieSeries() const {
    return PieSeries;
}


bool piemodel::ImportFromFile(const QString& FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    else{
        bool CorrectInput=true;
        QString line;
        QString x;
        qreal y;
        while (!file.atEnd() && CorrectInput) {
            line=file.readLine();
            x=line.split(',').first();
            y=line.split(',').last().toDouble(&CorrectInput);
            if(y<0)
               CorrectInput=false;
            else
                PieSeries->append(x,y);
        }
        if(!CorrectInput) {PieSeries->clear(); return false;}
        return true;
    }
}

bool piemodel::SaveFile(const QString &FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }
    else{
        file.resize(0);
        QTextStream stream(&file);
        QList<QPieSlice*> l=PieSeries->slices();
        for(QList<QPieSlice*>::const_iterator cit=l.begin();cit!=l.end();++cit){
            stream << (*cit)->label() << ',' << (*cit)->value() << '\n';
        }
    }
    return true;
}

void piemodel::AddtoChart(const QStringList& SList){
    QString label=SList.first();
    qreal value=SList.last().toDouble();
    PieSeries->append(label,value);
}

bool piemodel::RemovefromChart(const QStringList& SL){
    QString lable=SL.first();
    for(unsigned int i=0; i<PieSeries->count();++i){
        if(PieSeries->slices().at(i)->label()==lable){
            PieSeries->remove(PieSeries->slices().at(i));
            return true;
        }
    }
    return false;
}



