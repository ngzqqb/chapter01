/* two_point_line_module/TwoPoint.hpp */
#pragma once

#include "TwoPoint.hpp"
#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class Static : public QObject {
        Q_OBJECT
    public:
        Static();
        Q_SLOT QVariant createTwoPoint(double fX,double fY,double sX,double sY) const;
    public:
        static QObject * instance(QQmlEngine *, QJSEngine *);
    private:
        sstd_class(Static);
    };

}/*namespace sstd*/
