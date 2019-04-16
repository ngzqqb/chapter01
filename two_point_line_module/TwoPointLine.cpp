#include "TwoPointLine.hpp"

namespace sstd{

    TwoPointLine::TwoPointLine(QQuickItem * arg) :Super(arg) {
        thisLineWidth = 1.;
    }

    void TwoPointLine::setTwoPoint(const TwoPoint & arg){
        if( thisData == arg ) {
            return;
        }
        thisData = arg;
        twoPointChanged();
    }

    void TwoPointLine::setLineWidth(const double & arg){
        if( thisLineWidth == arg ){
            return;
        }
        thisLineWidth = arg;
        lineWidthChanged();
    }

    void TwoPointLine::setLineColor(const QColor & arg){
        if( thisLineColor == arg ){
            return;
        }
        thisLineColor = arg;
        lineColorChanged();
    }

}/*namespace sstd*/


