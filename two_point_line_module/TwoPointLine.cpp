#include "TwoPointLine.hpp"

namespace sstd {

    TwoPointLine::TwoPointLine(QQuickItem * arg) :Super(arg) {
        thisLineWidth = 1.;
        thisFlags = static_cast<std::size_t>(-1);
    }

    void TwoPointLine::setTwoPoint(const TwoPoint & arg) {
        if (thisData == arg) {
            return;
        }
        thisData = arg;
        thisFlags |= PointChanged_;
        twoPointChanged();
        this->update();
    }

    void TwoPointLine::setLineWidth(const double & arg) {
        if (thisLineWidth == arg) {
            return;
        }
        thisLineWidth = arg;
        thisFlags |= LineWidthChanged_;
        lineWidthChanged();
        this->update();
    }

    void TwoPointLine::setLineColor(const QColor & arg) {
        if (thisLineColor == arg) {
            return;
        }
        thisLineColor = arg;
        thisFlags |= LineColorChanged_;
        lineColorChanged();
        this->update();
    }

    class TwoLineNode : public QSGNode {
        TwoPointLine * const thisSuper;
    public:

        inline TwoLineNode(TwoPointLine * arg) : thisSuper(arg) {
        }

        inline void update() {

            if ((thisSuper->thisFlags&TwoPointLine::PointChanged_) ||
                (thisSuper->thisFlags&TwoPointLine::LineWidthChanged_)) {
                thisSuper->thisFlags &= (~TwoPointLine::LineWidthChanged_);
                thisSuper->thisFlags &= (~TwoPointLine::PointChanged_);
            }

            if (thisSuper->thisFlags&TwoPointLine::LineColorChanged_) {
                thisSuper->thisFlags &= (~TwoPointLine::LineColorChanged_);
            }

        }
    private:
        sstd_class(TwoLineNode);
    };

    QSGNode * TwoPointLine::updatePaintNode(QSGNode * argNode, QQuickItem::UpdatePaintNodeData *) {
        auto varNode = static_cast<TwoLineNode *>(argNode);
        if (varNode == nullptr) {
            //varNode = sstd_new< TwoLineNode >();
        }
        varNode->update();
        return varNode;
    }

}/*namespace sstd*/


