#include "basechart.h"

QString baseChart::getSavedFileName() const{
    return savedFileName;
}

baseChart::~baseChart(){

}

QChart::QChartView* baseChart::getChartView() const {
    return chartView;
}
