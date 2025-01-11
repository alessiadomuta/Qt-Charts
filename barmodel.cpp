#include "barmodel.h"

barmodel::barmodel():CAxis(new QBarCategoryAxis()),BSets(new QList<QBarSet*>()),BSeries(new QBarSeries()){

}

QList<QBarSet*>* barmodel::BarSets() const{return BSets;}

QBarSeries* barmodel::BarSeries() const {return BSeries;}

QBarCategoryAxis* barmodel::CategoryAxis() const {return CAxis;}

bool barmodel::ImportFromFile(const QString& FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    else{
        bool CorrectInput=true;
        QString line;
        line=file.readLine();
        unsigned int count=line.split(',').count();
        line.remove("\n");
        CAxis->append(line.split(','));
        QStringList StringList;
        while (!file.atEnd() && CorrectInput) {
            line=file.readLine();
            StringList=line.split(',');
            if(!StringList.isEmpty()){
                BSets->append(new QBarSet(StringList.takeFirst()));
                for(unsigned int j=0; j<StringList.count() && CorrectInput; ++j){
                    QString temp=StringList.at(j);
                    BSets->last()->append(temp.toDouble(&CorrectInput));
                    if(j>count-1){CorrectInput=false;}
                }
            }
        }
        return CorrectInput;
    }
}

bool barmodel::SaveFile(const QString &FileName){
    QFile file(FileName);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }
    else{
        file.resize(0);
        QTextStream stream(&file);
        stream << CAxis->at(0);
        for(unsigned int i=1; i<CAxis->count(); ++i){
            stream << ',' << CAxis->at(i);
        }
        stream << "\n";
        for(unsigned int j=0; j<BSets->count(); ++j){
            stream << BSets->at(j)->label();
            for(unsigned int k=0; k<BSets->at(j)->count(); ++k){
                stream << ',' << BSets->at(j)->at(k);
            }
            stream << "\n";
        }
        return true;
    }
}

void barmodel::AddtoModel(const QStringList& SList){
    unsigned int CategoryIndex=FindMakeCategory(SList.at(0));
    unsigned int BarSetIndex=FindMakeBarSet(SList.at(1));
    qreal value=SList.at(2).toDouble();
    if(BSets->at(BarSetIndex)->count()<CategoryIndex+1){
        unsigned int i=BSets->at(BarSetIndex)->count();
        for(;i<=CategoryIndex+1;++i){
                BSets->at(BarSetIndex)->append(0);}
    }
    BSets->at(BarSetIndex)->replace(CategoryIndex,value);
}

bool barmodel::RemovefromModel(const QStringList& SL){
    int CategoryIndex=FindCategory(SL.at(0));
    int BarSetIndex=FindBarSet(SL.at(1));
    if(CategoryIndex!=-1 && BarSetIndex!=-1){
         BSets->at(BarSetIndex)->replace(CategoryIndex,0);
         RemoveEmptyCategory(CategoryIndex);
         RemoveEmptyBarSet(BarSetIndex);
         return true;
    }
    else
        return false;
}

unsigned int barmodel::FindMakeCategory(const QString& cat){
    QStringList l=CAxis->categories();
    for(unsigned int i=0; i<l.count(); ++i){
        QString s=l.at(i).split('\n').first();
        if(s==cat) {return i;}
    }
    CAxis->append(cat);
    return CAxis->count()-1;
}

unsigned int barmodel::FindMakeBarSet(const QString& bar){
    for(unsigned int i=0; i<BSets->count(); ++i){
        if(BSets->at(i)->label()==bar){return i;}
    }
    BSets->append(new QBarSet(bar));
    return BSets->count()-1;
}

int barmodel::FindCategory(const QString & cat) const{
    QStringList l=CAxis->categories();
    for(unsigned int i=0; i<l.count(); ++i){
        QString s=l.at(i).split('\n').first();
        if(s==cat) {return i;}
    }
    return -1;
}

int barmodel::FindBarSet(const QString & bar) const{
    for(unsigned int i=0; i<BSets->count(); ++i){
        if(BSets->at(i)->label()==bar){return i;}
    }
    return -1;
}

bool barmodel::RemoveEmptyCategory(unsigned int CatIndex){
    for(unsigned int BSIndex=0; BSIndex<BSets->count(); ++BSIndex){
        if(BSets->at(BSIndex)->at(CatIndex)!=0) return false;
    }
    CAxis->remove(CAxis->at(CatIndex));
    for(unsigned int BSIndex=0; BSIndex<BSets->count(); ++BSIndex){
        BSets->at(BSIndex)->remove(CatIndex);
    }
    return true;
}

bool barmodel::RemoveEmptyBarSet(unsigned int BarIndex){
    for(unsigned int CIndex=0; CIndex<CAxis->count(); ++CIndex){
        if(BSets->at(BarIndex)->at(CIndex)!=0){return false;}
    }
    BSets->removeAt(BarIndex);
    return true;
}






