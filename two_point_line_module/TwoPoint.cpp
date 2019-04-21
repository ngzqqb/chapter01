#include "TwoPoint.hpp"

namespace sstd{

    TwoPoint::TwoPoint() : thisFirstPoint{-1.,0.},
        thisSecondPoint{1.,0.}{
    }

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











