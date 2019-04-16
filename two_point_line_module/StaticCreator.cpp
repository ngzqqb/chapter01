#include "StaticCreator.hpp"

namespace sstd {

    Static::Static() {
        QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    }

    TwoPoint Static::createTwoPoint(double fX, double fY, double sX, double sY) const {
        TwoPoint varAns;
        varAns.setFirstPoint({ fX,fY });
        varAns.setSecondPoint({ sX,sY });
        return varAns;
    }

    QObject * Static::instance(QQmlEngine *, QJSEngine *) {
        static Static varAns;
        return &varAns;
    }

}/*namespace sstd*/










