/* two_point_line_module/TwoPoint.hpp */
#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class TwoPoint {
        Q_GADGET
    private:
        QPointF thisFirstPoint;
        QPointF thisSecondPoint;
    public:
        TwoPoint();
    public:
        Q_INVOKABLE QPointF getFirstPoint() const;
        Q_INVOKABLE QPointF getSecondPoint()const;

        Q_INVOKABLE void setFirstPoint(const QPointF & varPoint);
        Q_INVOKABLE void setSecondPoint(const QPointF & varPoint);
    public:
        friend bool operator==(const TwoPoint &, const TwoPoint &);
    public:
        sstd_default_copy_create(TwoPoint);
    private:
        sstd_class(TwoPoint);
    };

    inline bool operator==(const TwoPoint & a, const TwoPoint & b) {
        if (&a == &b) {
            return true;
        }
        if (a.thisFirstPoint != b.thisFirstPoint) {
            return false;
        }
        return a.thisSecondPoint == b.thisSecondPoint;
    }

}/*namespace sstd*/

