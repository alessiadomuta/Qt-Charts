#include "barchart.h"

barchart::barchart():baseChart(),model(new barmodel()){
    chartView=new QChart::QChartView(this);
    addSeries(model->BarSeries());
    legend()->setVisible(true);
    createDefaultAxes();
    setAxisX(model->CategoryAxis(),model->BarSeries());
    chartView->setRenderHint(QPainter::Antialiasing);
    setAnimationOptions(QChart::AllAnimations);
    setTheme(QChart::ChartThemeBlueNcs);
}

bool barchart::ImportFromFile(const QString& FileName){
    Clear();
    if(model->ImportFromFile(FileName)){savedFileName=FileName;}
    else {Clear(); return false;}
    Draw();
    return true;
}

bool barchart::SaveFile(const QString &FileName){
    if(model->SaveFile(FileName)) {savedFileName=FileName; return true;}
    return false;
}

void barchart::Clear(){
    removeSeries(model->BarSeries());
    removeAxis(model->CategoryAxis());
    delete model->BarSets();
    removeAxis(axisY());
    model=new barmodel();
}

void barchart::Draw(){
    model->BarSeries()->append(*(model->BarSets()));
    addSeries(model->BarSeries());
    createDefaultAxes();
    setAxisX(model->CategoryAxis(),model->BarSeries());
}

void barchart::Redraw(){
    QList<QBarSet*>* aux=new QList<QBarSet*>(*(model->BarSets()));
    QStringList* categories=new QStringList(model->CategoryAxis()->categories());
    Clear();
    model->BarSets()->append(*aux);
    model->CategoryAxis()->append(*categories);
    Draw();
}

void barchart::AddtoChart( const QStringList& SL){
    if(!SL.at(0).isEmpty() && !SL.at(1).isEmpty() && !SL.at(2).isEmpty()){
        model->AddtoModel(SL);
        Redraw();
    }
}

bool barchart::RemovefromChart(const QStringList& SL){
    if(!SL.at(0).isEmpty() && !SL.at(1).isEmpty()){
        if(model->RemovefromModel(SL)){
           Redraw();
           return true;
        }
        return false;
    }
}



