#include "StaticCreator.hpp"

namespace sstd {

    Static::Static() {
        QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    }

    QVariant Static::createTwoPoint(double fX, double fY, double sX, double sY) const {
        TwoPoint varAns;
        varAns.setFirstPoint({ fX,fY });
        varAns.setSecondPoint({ sX,sY });
        return QVariant::fromValue(varAns);
    }

    QObject * Static::instance(QQmlEngine *, QJSEngine *) {
        static Static varAns;
        return &varAns;
    }

}/*namespace sstd*/
