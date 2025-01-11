#include "startview.h"

startview::startview():userIn(nullptr) {

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    mainLayout->addLayout(createVerticalLayout());
    mainLayout->addLayout(createButtonsLayout());

    createFileLayout();

    setLayout(mainLayout);
    //resize(QSize(800,600));

    createPie();

}

QLayout* startview::createButtonsLayout(){

    QDockWidget* dock=new QDockWidget(this);
    dock->setTitleBarWidget(new QWidget());
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    dock->setFixedSize(1024,64);

    QWidget* DockWidget = new QWidget(dock);

    QHBoxLayout* buttonsLayout = new QHBoxLayout(DockWidget);

    QPushButton *pie_button = new QPushButton("&Pie", DockWidget);  
    connect(pie_button,SIGNAL(clicked(bool)),this,SLOT(createPie()));

    QPushButton *line_button = new QPushButton("&Line", DockWidget);
    connect(line_button,SIGNAL(clicked(bool)),this,SLOT(createLine()));

    QPushButton *bar_button = new QPushButton("&Bar", DockWidget);
    connect(bar_button,SIGNAL(clicked(bool)),this,SLOT(createBar()));

    QPushButton *spline_button = new QPushButton("&Spline", DockWidget);
    connect(spline_button,SIGNAL(clicked(bool)),this,SLOT(createSpline()));

    QPushButton *scatter_button = new QPushButton("&Scatter", DockWidget);
    connect(scatter_button,SIGNAL(clicked(bool)),this,SLOT(createScatter()));


    buttonsLayout->addWidget(pie_button);
    buttonsLayout->addWidget(line_button);
    buttonsLayout->addWidget(bar_button);
    buttonsLayout->addWidget(spline_button);
    buttonsLayout->addWidget(scatter_button);

    dock->setWidget(DockWidget);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    return buttonsLayout;

}

QLayout* startview::createVerticalLayout(){

    QDockWidget* dockV=new QDockWidget(this);
    dockV->setTitleBarWidget(new QWidget());
    dockV->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockV->setFixedSize(400,704);

    QWidget* DockWidgetV = new QWidget(dockV);
    QVBoxLayout* layout=new QVBoxLayout(DockWidgetV);

    userActions=new QWidget(DockWidgetV);
    QVBoxLayout* VLayout=new QVBoxLayout(userActions);
    userActions->setLayout(VLayout);

    layout->addWidget(userActions);

    dockV->setWidget(DockWidgetV);
    dockV->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea,dockV);

    return layout;

}

void startview::createFileLayout(){

    fileView=new QGroupBox("File Action",userActions);

    QPushButton* openButton=new QPushButton("Open",userActions);
    connect(openButton,SIGNAL(clicked(bool)),this,SLOT(openFile()));

    QPushButton* saveAsButton=new QPushButton(tr("Save as"),userActions);
    connect(saveAsButton,SIGNAL(clicked(bool)),this,SLOT(saveAsFile()));


    QHBoxLayout* FileH=new QHBoxLayout(fileView);
    FileH->addWidget(openButton);
    FileH->addWidget(saveAsButton);

    userActions->layout()->addWidget(fileView);

}

void startview::userInput(chartTypes type){

    userActions->layout()->removeWidget(userIn);
    delete userIn;
    userIn = new userinputs(type, userActions);;

    userActions->layout()->addWidget(userIn);

    connect(userIn,SIGNAL(insertData()),this,SLOT(addData()));
    connect(userIn,SIGNAL(removeData()),this,SLOT(deleteData()));
}

void startview::openFile() const{

    QString fileName = QFileDialog::getOpenFileName(fileView,"Open csv file", "/home","Chart files(*.csv)");
    if(!chart->ImportFromFile(fileName)){
        QMessageBox::warning(userIn,"Error","Couldn't open the file",QMessageBox::Ok);
    }

}

void startview::saveAsFile() const{

    QString fileName=QFileDialog::getSaveFileName(fileView,"Save as csv file", "/home","Chart files(*.csv)");
    if(chart->SaveFile(fileName)){
        QMessageBox::warning(userIn,"Message","Save Completed",QMessageBox::Ok);
    }
    else{
        QMessageBox::warning(userIn,"Error","Save Failed",QMessageBox::Ok);
    }

}

void startview::createPie(){

    chart = new piechart();
    setCentralWidget(chart->getChartView());
    userInput(pie);

}
void startview::createLine(){

    chart = new linechart();
    setCentralWidget(chart->getChartView());
    userInput(line);

}
void startview::createBar(){

    chart = new barchart();
    setCentralWidget(chart->getChartView());
    userInput(bar);

}
void startview::createSpline(){

    chart = new splinechart();
    setCentralWidget(chart->getChartView());
    userInput(spline);

}
void startview::createScatter(){

    chart = new scatterchart();
    setCentralWidget(chart->getChartView());
    userInput(scatter);

}

void startview::addData(){
    if(userIn->getTipo()==pie){
        if(!chart->RemovefromChart(userIn->getData())){chart->AddtoChart(userIn->getData());}
        else {chart->AddtoChart(userIn->getData());}
    }
    else{chart->AddtoChart(userIn->getData());}
}

void startview::deleteData(){

    if(!chart->RemovefromChart(userIn->getData())){QMessageBox::warning(this,"Error","No match found",QMessageBox::Ok);}

}
