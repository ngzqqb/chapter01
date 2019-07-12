#include "SubWindowBasic.hpp"

namespace sstd {

    inline static constexpr auto theRenderHints() {
        return QPainter::Antialiasing |
            QPainter::TextAntialiasing |
            QPainter::SmoothPixmapTransform |
            QPainter::HighQualityAntialiasing;
    }

    SubWindowBasic::SubWindowBasic(const QString & arg) {
        this->setObjectName(arg);
        this->setAlignment(Qt::AlignCenter);
        {
            auto varScene = sstd_virtual_new<QGraphicsScene>(this);
            this->setScene(varScene);
        }
        this->setRenderHints(theRenderHints());
    }

    void SubWindowBasic::printToPdf(const QString & argFileName) const {

        auto varScene = this->scene();
        auto varBoundingRect =
            varScene->itemsBoundingRect();

        const auto varBestWidth = std::min<qreal>(bestWidth(), varBoundingRect.width());
        const auto varRate = varBestWidth / varBoundingRect.width();
        const auto varBestHeight = varBoundingRect.height() * varRate;

        QFile varPDFFile{ argFileName };
        if (false == varPDFFile.open(QIODevice::WriteOnly)) {
            return;
        }

        auto cRect = [](const auto & p,
            const qreal & w, const qreal & h)->QRectF {
            return{ p.x() - 0.5f*w,p.y() - 0.5f*h,w,h };
        };

        QPdfWriter varWriter{ &varPDFFile };

        {
            varWriter.setMargins({ 0,0,0,0 });
            const QPageSize varSize{
               QSizeF{ varBestWidth,varBestHeight } ,QPageSize::Point };
            varWriter.setPageSize(varSize);
        }

        QPainter varPainter{ &varWriter };
        varPainter.setRenderHints(renderHints());
        varScene->render(&varPainter,
            {/* target rectangle */ },
            cRect(bestCenter() ? *bestCenter() : varBoundingRect.center(),
                varBestWidth, varBestHeight));

    }

}/*namespace sstd*/
