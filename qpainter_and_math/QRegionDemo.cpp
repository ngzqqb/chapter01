#include "QRegionDemo.hpp"

namespace sstd {

    QRegionDemo::QRegionDemo()
        : SubWindowBasic(QStringLiteral("QRegionDemo")) {
        auto varScene = this->scene();
        assert(varScene);
        QRegion varRegion{ QRect{0,0,100,100} };
        {
            QRegion varSubRegion{ QRect{50,50,100,100} , QRegion::Ellipse };
            varRegion -= varSubRegion;
        }
        QPainterPath varPath;
        varPath.addRegion(varRegion);
        varScene->addPath(varPath, QPen{ QColor(255,1,1) }, QBrush{ QColor(1,128,1) });

        varPath.translate(150, 0);
        varScene->addPath(varPath.simplified(), QPen{ QColor(255,1,1) }, QBrush{ QColor(1,128,1) });
    }

}/*namespace sstd*/

//QRegion 用于求整形 矩形和椭圆形的 +() -() &() ^()
