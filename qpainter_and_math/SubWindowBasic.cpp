﻿#include "SubWindowBasic.hpp"

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
            QPainter::HighQualityAntialiasing);
    }

    inline static QRectF cRect(const QPointF & p,
        const qreal & w, const qreal & h) {
        return{ p.x() - 0.5*w,p.y() - 0.5*h,w,h };
    }

    void SubWindowBasic::printToPdf(const QString & argFileName) const {

        auto varScene = this->scene();
        auto varBoundingRect =
            varScene->itemsBoundingRect();

        auto varBestWidth = std::min<qreal>(bestWidth(), varBoundingRect.width());
        const auto varRate = varBestWidth / varBoundingRect.width();
        auto varBestHeight = varBoundingRect.height() * varRate;

        QFile varPDFFile{ argFileName };
        if (false == varPDFFile.open(QIODevice::WriteOnly)) {
            return;
        }

        QPdfWriter varWriter{ &varPDFFile };

        {
            varWriter.setMargins({ 0,0,0,0 });
            const QPageSize varSize{
               QSizeF{ varBestWidth,varBestHeight } ,QPageSize::Point };
            varWriter.setPageSize(varSize);
        }

        QPainter varPainter{ &varWriter };
        varScene->render(&varPainter,
            {/*target*/ },
            cRect(bestCenter() ? *bestCenter() : varBoundingRect.center(),
                varBestWidth, varBestHeight));

    }

}/*namespace sstd*/
