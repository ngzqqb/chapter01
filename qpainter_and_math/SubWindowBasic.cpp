#include "SubWindowBasic.hpp"

namespace sstd {

    SubWindowBasic::SubWindowBasic(const QString & arg) {
        this->setObjectName(arg);
        this->setAlignment(Qt::AlignCenter);
        {
            auto varScene = sstd_virtual_new<QGraphicsScene>(this);
            this->setScene(varScene);
        }
        this->setRenderHints(
            QPainter::Antialiasing |
            QPainter::TextAntialiasing |
            QPainter::SmoothPixmapTransform |
            QPainter::HighQualityAntialiasing );
    }

}/*namespace sstd*/
