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
            QPainter::HighQualityAntialiasing);
    }

    void SubWindowBasic::printToPdf(const QString & argFileName) const {

        auto varScene = this->scene();
        auto varBoundingRect =
            varScene->itemsBoundingRect();

        const qreal varBestWidth = bestWidth();
        const qreal varBestHeight = bestHeight();


        QFile varPDFFile{ argFileName };
        if (false == varPDFFile.open(QIODevice::WriteOnly)) {
            return;
        }

        QPdfWriter varWriter{ &varPDFFile };

        {
            varWriter.setMargins({ 0,0,0,0 });
            const QPageSize varSize{
               varBoundingRect.size() ,QPageSize::Point };
            varWriter.setPageSize(varSize);
        }

        QPainter varPainter{ &varWriter };
        varScene->render(&varPainter,
            {/*target*/ },
            {/*source*/ });

    }

}/*namespace sstd*/
