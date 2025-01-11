#include "scatterchart.h"

scatterchart::scatterchart():baseChart(),model(new scattermodel()){
    chartView=new QChart::QChartView(this);
    legend()->hide();
    addSeries(model->getScatterSeries());
    createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);
    setAnimationOptions(QChart::AllAnimations);
    setTheme(QChart::ChartThemeBlueNcs);
}

bool scatterchart::ImportFromFile(const QString& FileName){
    Clear();
    if(model->ImportFromFile(FileName)) {savedFileName=FileName;Draw(); return true;}
    else{model->getScatterSeries()->clear();Draw();return false;}
}

bool scatterchart::SaveFile(const QString &FileName){
    if(model->SaveFile(FileName)){savedFileName=FileName;return true;}
    else{return false;}
}

void scatterchart::Clear(){
    removeAllSeries();
    removeAxis(axisX());
    removeAxis(axisY());
    model=new scattermodel();
}

void scatterchart::Draw(){
    addSeries(model->getScatterSeries());
    createDefaultAxes();
    model->getScatterSeries()->setPointsVisible(true);
    model->getScatterSeries()->setPointLabelsVisible(true);
    QFont LableFont;
    LableFont.setBold(true);
    LableFont.setPointSize(11);
    model->getScatterSeries()->setPointLabelsFont(LableFont);
    zoom(0.8);
}

void scatterchart::Redraw(){
    QList<QPointF> v=model->getScatterSeries()->points();
    Clear();
    model->getScatterSeries()->append(v);
    Draw();
}

void scatterchart::AddtoChart(const QStringList& SList){
    if(!SList.first().isEmpty() && !SList.last().isEmpty()){
        model->AddtoChart(SList);
        Redraw();
    }
}

bool scatterchart::RemovefromChart(const QStringList& SL){
    if(!SL.first().isEmpty() && !SL.last().isEmpty()){
        if(model->RemovefromChart(SL)){Redraw(); return true;}
        else return false;
    }
}
