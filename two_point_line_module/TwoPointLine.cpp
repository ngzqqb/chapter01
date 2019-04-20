#include "TwoPointLine.hpp"

namespace sstd {

    TwoPointLine::TwoPointLine(QQuickItem * arg) :Super(arg) {
        this->setFlag(QQuickItem::ItemHasContents, true);
        thisNodeData = sstd_make_shared<TwoPointLineNodeData>();
    }

    TwoPointLine::~TwoPointLine() {
    }

    void TwoPointLine::componentComplete() {
        Super::componentComplete();
    }

    extern std::array< QPointF, 4 > updateGeometryByTwoPoints(QPointF varStartPoint,
        QPointF varEndPoint,
        double varLineWidth,
        bool & argIsEmpty);

    void TwoPointLine::updateWidthHeight() {
        bool varIsEmpty{ false };
        auto varTwoPoint = thisNodeData->getTwoPoint();
        auto varPoints = updateGeometryByTwoPoints(varTwoPoint.getFirstPoint(),
            varTwoPoint.getSecondPoint(),
            thisNodeData->getLineWidth(),
            varIsEmpty);
        if (varIsEmpty) {
            this->setWidth(0);
            this->setHeight(0);
        } else {
            {
                auto varXLimit = std::minmax_element(varPoints.begin(), varPoints.end(),
                    [](const auto & varI, const auto & varJ) {
                    return varI.x() < varJ.x();
                });
                this->setWidth(varXLimit.second->x() - varXLimit.first->x());
            }
            {
                auto varXLimit = std::minmax_element(varPoints.begin(), varPoints.end(),
                    [](const auto & varI, const auto & varJ) {
                    return varI.y() < varJ.y();
                });
                this->setHeight(varXLimit.second->y() - varXLimit.first->y());
            }
        }
    }

    void TwoPointLine::setTwoPoint(const QVariant & arg) {
        if (qMetaTypeId<sstd::TwoPoint>() != arg.userType()) {
            qWarning() << QStringLiteral("you input error type "
                ", you should input sstd::TwoPoint!") << arg;
            return;
        }
        if (thisNodeData->setTwoPoint(arg.value<sstd::TwoPoint>())) {
            this->updateWidthHeight();
            this->twoPointChanged();
            this->update();
        }
    }

    void TwoPointLine::setLineWidth(const double & arg) {
        if (thisNodeData->setLineWidth(arg)) {
            this->updateWidthHeight();
            this->lineWidthChanged();
            this->update();
        }
    }

    void TwoPointLine::setLineColor(const QColor & arg) {
        if (thisNodeData->setLineColor(arg)) {
            this->lineColorChanged();
            this->update();
        }
    }

    QSGNode * TwoPointLine::updatePaintNode(QSGNode * argNode, QQuickItem::UpdatePaintNodeData *) {
        auto varNode = static_cast<TwoPointLineNode*>(argNode);
        if (varNode == nullptr) {
            varNode = sstd_new<TwoPointLineNode>(thisNodeData);
        }
        varNode->updateTheNode();
        return varNode;
    }

}/*namespace sstd*/


