﻿#include "TwoPointLine.hpp"

namespace sstd {

    TwoPointLine::TwoPointLine(QQuickItem * arg) :Super(arg) {
        this->setFlag(QQuickItem::ItemHasContents, true);
        thisNodeData = sstd_make_shared<TwoPointLineNodeData>();
    }

    TwoPointLine::~TwoPointLine() {
        if (thisNode && (nullptr == thisNode->parent())) {
            delete thisNode;
        }
    }

    void TwoPointLine::componentComplete() {
        Super::componentComplete();
        thisNode = sstd_new<TwoPointLineNode>(thisNodeData);
    }

    void TwoPointLine::setTwoPoint(const QVariant & arg) {
        if (qMetaTypeId<sstd::TwoPoint>() != arg.userType()) {
            qWarning() << QStringLiteral("you input error type!") << arg;
            return;
        }
        if (thisNodeData->setTwoPoint(arg.value<sstd::TwoPoint>())) {
            this->twoPointChanged();
        }
    }

    void TwoPointLine::setLineWidth(const double & arg) {
        if (thisNodeData->setLineWidth(arg)) {
            this->lineWidthChanged();
        }
    }

    void TwoPointLine::setLineColor(const QColor & arg) {
        if (thisNodeData->setLineColor(arg)) {
            this->lineColorChanged();
        }
    }

    QSGNode * TwoPointLine::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *) {
        thisNode->updateTheNode();
        return thisNode;
    }

    

}/*namespace sstd*/


