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

    void TwoPointLine::setTwoPoint(const QVariant & arg) {
        if (qMetaTypeId<sstd::TwoPoint>() != arg.userType()) {
            qWarning() << QStringLiteral("you input error type "
                ", you should input sstd::TwoPoint!") << arg;
            return;
        }
        if (thisNodeData->setTwoPoint(arg.value<sstd::TwoPoint>())) {
            this->twoPointChanged();
            this->update();
        }
    }

    void TwoPointLine::setLineWidth(const double & arg) {
        if (thisNodeData->setLineWidth(arg)) {
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
        thisNodeData->setWidth(this->width());
        thisNodeData->setHeight(this->height());
        varNode->updateTheNode();
        return varNode;
    }

}/*namespace sstd*/
