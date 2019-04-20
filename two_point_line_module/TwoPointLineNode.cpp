#include "TwoPointLineNode.hpp"

namespace sstd{

    bool TwoPointLineNode::setTwoPoint(const TwoPoint & arg){
        if( arg == thisPoints ){
            return false;
        }
        thisPoints = arg;
        thisState.set<TwoPointLineNodeState::PointChanged>();
        return true;
    }

    bool TwoPointLineNode::setLineWidth(const double & arg){
        if( arg == thisLineWidth ){
            return false;
        }
        thisLineWidth = arg;
        thisState.set<TwoPointLineNodeState::LineWidthChanged>();
        return true;
    }

    bool TwoPointLineNode::setLineColor(const QColor & arg){
        if( arg == thisLineColor ){
            return false;
        }
        thisLineColor = arg;
        thisState.set<TwoPointLineNodeState::LineColorChanged>();
        return true;
    }

    template<bool IsConstruct>
    void TwoPointLineNode::updateTheNode(){

        if( thisState.test<TwoPointLineNodeState::LineWidthChanged>() ||
            thisState.test<TwoPointLineNodeState::PointChanged>()){

            if constexpr(!IsConstruct){
            }
        }

        if( thisState.test<TwoPointLineNodeState::LineColorChanged>() ){

            if constexpr(!IsConstruct){
            }
        }

        thisState.clearAll();

    }

    TwoPointLineNode::TwoPointLineNode(){
        thisState.setAll();
        updateTheNode();
    }

}/*namespace sstd*/


