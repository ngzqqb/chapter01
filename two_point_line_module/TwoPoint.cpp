﻿#include "TwoPoint.hpp"

namespace sstd{

    TwoPoint::TwoPoint() : thisFirstPoint{0.,0.},
        thisSecondPoint{1.,1.}{}

    QPointF TwoPoint::getFirstPoint() const{
        return thisFirstPoint;
    }

    QPointF TwoPoint::getSecondPoint()const{
        return thisSecondPoint;
    }

    void TwoPoint::setFirstPoint(const QPointF & varPoint){
        thisFirstPoint=varPoint;
    }

    void TwoPoint::setSecondPoint(const QPointF & varPoint){
        thisSecondPoint=varPoint;
    }

}/*namespace sstd*/











