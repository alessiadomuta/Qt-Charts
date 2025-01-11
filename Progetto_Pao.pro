QT       += core gui

QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barchart.cpp \
    barmodel.cpp \
    basechart.cpp \
    linechart.cpp \
    linemodel.cpp \
    main.cpp \
    mainwindow.cpp \
    piechart.cpp \
    piemodel.cpp \
    scatterchart.cpp \
    scattermodel.cpp \
    splinechart.cpp \
    splinemodel.cpp \
    startview.cpp \
    userinputs.cpp

HEADERS += \
    barchart.h \
    barmodel.h \
    basechart.h \
    linechart.h \
    linemodel.h \
    mainwindow.h \
    piechart.h \
    piemodel.h \
    scatterchart.h \
    scattermodel.h \
    splinechart.h \
    splinemodel.h \
    startview.h \
    userinputs.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
