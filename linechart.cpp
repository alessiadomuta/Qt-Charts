#include "linechart.h"

linechart::linechart():baseChart(),model(new linemodel()){
    chartView=new QChart::QChartView(this);
    legend()->hide();
    addSeries(model->GetLineSeries());
    createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);
    setAnimationOptions(QChart::AllAnimations);
    setTheme(QChart::ChartThemeBlueNcs);
}

bool linechart::ImportFromFile(const QString& FileName){
    Clear();
    if(model->ImportFromFile(FileName)) {savedFileName=FileName;Draw(); return true;}
    else{model->GetLineSeries()->clear();Draw();return false;}
}

bool linechart::SaveFile(const QString &FileName){
    if(model->SaveFile(FileName)){savedFileName=FileName;return true;}
    else{return false;}
}

void linechart::Clear(){
    removeAllSeries();
    removeAxis(axisX());
    removeAxis(axisY());
    model=new linemodel();
}

void linechart::Draw(){
    addSeries(model->GetLineSeries());
    createDefaultAxes();
    model->GetLineSeries()->setPointsVisible(true);
    model->GetLineSeries()->setPointLabelsVisible(true);
    QFont LableFont;
    LableFont.setBold(true);
    LableFont.setPointSize(11);
    model->GetLineSeries()->setPointLabelsFont(LableFont);
    zoom(0.8);
}

void linechart::Redraw(){
    QList<QPointF> v=model->GetLineSeries()->points();
    Clear();
    model->GetLineSeries()->append(v);
    Draw();
}

void linechart::AddtoChart(const QStringList& SList){
    if(!SList.first().isEmpty() && !SList.last().isEmpty()){
        model->AddtoChart(SList);
        Redraw();
    }
}

bool linechart::RemovefromChart(const QStringList& SL){
    if(!SL.first().isEmpty() && !SL.last().isEmpty()){
        if(model->RemovefromChart(SL)){Redraw(); return true;}
        else return false;
    }
}
