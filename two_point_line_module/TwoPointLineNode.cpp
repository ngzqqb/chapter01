#include "TwoPointLineNode.hpp"

namespace sstd {

    bool TwoPointLineNodeData::setTwoPoint(const TwoPoint & arg) {
        if (arg == thisPoints) {
            return false;
        }
        thisPoints = arg;
        thisState.set<TwoPointLineNodeState::PointChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setLineWidth(const double & arg) {
        if (arg == thisLineWidth) {
            return false;
        }
        thisLineWidth = arg;
        thisState.set<TwoPointLineNodeState::LineWidthChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setLineColor(const QColor & arg) {
        if (arg == thisLineColor) {
            return false;
        }
        thisLineColor = arg;
        thisState.set<TwoPointLineNodeState::LineColorChanged>();
        return true;
    }

    void TwoPointLineNode::updateTheNode() {

        if (thisData->isChanged<TwoPointLineNodeState::LineWidthChanged>() ||
            thisData->isChanged<TwoPointLineNodeState::PointChanged>()) {
        }

        if (thisData->isChanged<TwoPointLineNodeState::LineColorChanged>()) {
        }

        thisData->clearAllChanged();

    }

    TwoPointLineNode::TwoPointLineNode(std::shared_ptr<TwoPointLineNodeData> arg) :
        thisData{ std::move(arg) } {
    }

    TwoPointLineNodeData::TwoPointLineNodeData() {
        thisState.setAll();
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/

