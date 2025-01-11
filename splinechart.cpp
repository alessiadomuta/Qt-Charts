#include "splinechart.h"

splinechart::splinechart():baseChart(),model(new splinemodel()){
    chartView=new QChart::QChartView(this);
    legend()->hide();
    addSeries(model->getSplineSeries());
    createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);
    setAnimationOptions(QChart::AllAnimations);
    setTheme(QChart::ChartThemeBlueNcs);
}

bool splinechart::ImportFromFile(const QString& FileName){
    Clear();
    if(model->ImportFromFile(FileName)) {savedFileName=FileName;Draw(); return true;}
    else{model->getSplineSeries()->clear();Draw();return false;}
}

bool splinechart::SaveFile(const QString &FileName){
    if(model->SaveFile(FileName)){savedFileName=FileName;return true;}
    else{return false;}
}

void splinechart::Clear(){
    removeAllSeries();
    removeAxis(axisX());
    removeAxis(axisY());
    model=new splinemodel();
}

void splinechart::Draw(){
    addSeries(model->getSplineSeries());
    createDefaultAxes();
    model->getSplineSeries()->setPointsVisible(true);
    model->getSplineSeries()->setPointLabelsVisible(true);
    QFont LableFont;
    LableFont.setBold(true);
    LableFont.setPointSize(11);
    model->getSplineSeries()->setPointLabelsFont(LableFont);
    zoom(0.8);
}

void splinechart::Redraw(){
    QList<QPointF> v=model->getSplineSeries()->points();
    Clear();
    model->getSplineSeries()->append(v);
    Draw();
}

void splinechart::AddtoChart(const QStringList& SList){
    if(!SList.first().isEmpty() && !SList.last().isEmpty()){
        model->AddtoChart(SList);
        Redraw();
    }
}

bool splinechart::RemovefromChart(const QStringList& SL){
    if(!SL.first().isEmpty() && !SL.last().isEmpty()){
        if(model->RemovefromChart(SL)){Redraw(); return true;}
        else return false;
    }
}
