#pragma once

#include <sstd_qt_qml_quick_library.hpp>
#include "TwoPoint.hpp"

namespace sstd{

    enum class TwoPointLineNodeState : std::size_t {
        PointChanged,
        LineWidthChanged ,
        LineColorChanged ,
        Size
    };

    class TwoPointLineNode : public QSGGeometryNode {
    public:
        TwoPointLineNode();
    public:
        inline TwoPoint getTwoPoint() const;
        inline double getLineWidth() const;
        inline QColor getLineColor() const;
    public:
        bool setTwoPoint(const TwoPoint &);
        bool setLineWidth(const double &);
        bool setLineColor(const QColor &);
    public:
        void updateTheNode();
    private:
        TwoPoint thisPoints;
        double thisLineWidth;
        QColor thisLineColor;
        sstd::QuickFlags<TwoPointLineNodeState::Size> thisState;
    private:
        sstd_class(TwoPointLineNode);
    };

    inline TwoPoint TwoPointLineNode::getTwoPoint() const{
        return thisPoints;
    }

    inline double TwoPointLineNode::getLineWidth() const{
        return thisLineWidth;
    }

    inline QColor TwoPointLineNode::getLineColor() const {
        return thisLineColor;
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/









