#include "TwoPointLine.hpp"

namespace sstd {

    TwoPointLine::TwoPointLine(QQuickItem * arg) :Super(arg) {
        this->setFlag(QQuickItem::ItemHasContents, true);
    }

    TwoPointLine::~TwoPointLine(){
        if( thisNode && (nullptr == thisNode->parent()) ){
            delete thisNode;
        }
    }

    void TwoPointLine::setTwoPoint(const TwoPoint & arg) {
        assert( thisNode );
        if( thisNode->setTwoPoint(arg) ){
            this->twoPointChanged();
        }
    }

    void TwoPointLine::setLineWidth(const double & arg) {
            assert( thisNode );
            if( thisNode->setLineWidth(arg) ){
                this->lineWidthChanged();
            }
    }

    void TwoPointLine::setLineColor(const QColor & arg) {
        assert( thisNode );
        if( thisNode->setLineColor(arg) ){
            this->lineColorChanged();
        }
    }

    QSGNode * TwoPointLine::updatePaintNode(QSGNode *  , QQuickItem::UpdatePaintNodeData *) {
        assert( thisNode );
        thisNode->updateTheNode();
        return thisNode;
    }

}/*namespace sstd*/


