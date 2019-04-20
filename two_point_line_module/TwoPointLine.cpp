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

        double varWidth, varHeight;
        constexpr auto varLineWidth = 0.5;

        {
            auto varTwoPoint = thisNodeData->getTwoPoint();
            auto varP1 = varTwoPoint.getFirstPoint();
            auto varP2 = varTwoPoint.getSecondPoint();
            varWidth = std::abs(varP1.x() - varP2.x());
            varHeight = std::abs(varP1.y() - varP2.y());
        }

        constexpr const auto varLimit = std::numeric_limits<float>::epsilon();
        bool varLimitAns[3]{
            (varWidth < varLimit),
            (varHeight < varLimit)
        };
        varLimitAns[2] = (varLimitAns[1]) && (varLimitAns[0]);

        if (varLimitAns[2]) {
            this->setWidth(0);
            this->setHeight(0);
            return;
        }

        this->setWidth(varLimitAns[0] ? varLineWidth : varWidth);
        this->setHeight(varLimitAns[1] ? varLineWidth : varHeight);
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


