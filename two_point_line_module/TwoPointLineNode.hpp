#pragma once

#include <sstd_qt_qml_quick_library.hpp>
#include "TwoPoint.hpp"

namespace sstd {

    enum class TwoPointLineNodeState : std::size_t {
        PointChanged,
        LineWidthChanged,
        LineColorChanged,
        Size
    };

    class TwoPointLineNodeData {
    public:
        TwoPointLineNodeData();
    public:
        inline TwoPoint getTwoPoint() const;
        inline double getLineWidth() const;
        inline QColor getLineColor() const;
    public:
        bool setTwoPoint(const TwoPoint &);
        bool setLineWidth(const double &);
        bool setLineColor(const QColor &);
    public:
        template<TwoPointLineNodeState>
        inline bool isChanged() const;
        inline void clearAllChanged();
    private:
        TwoPoint thisPoints;
        double thisLineWidth;
        QColor thisLineColor;
        sstd::QuickFlags<TwoPointLineNodeState::Size> thisState;
    private:
        sstd_class(TwoPointLineNodeData);
    };

    template<TwoPointLineNodeState I>
    inline bool TwoPointLineNodeData::isChanged() const {
        return thisState.test<I>();
    }

    inline void TwoPointLineNodeData::clearAllChanged() {
        thisState.clearAll();
    }

    class TwoPointLineNode : public QSGGeometryNode {
    public:
        TwoPointLineNode(std::shared_ptr<TwoPointLineNodeData>);
    public:
        void updateTheNode();
    private:
        std::shared_ptr<TwoPointLineNodeData> thisData;
    private:
        sstd_class(TwoPointLineNode);
    };

    inline TwoPoint TwoPointLineNodeData::getTwoPoint() const {
        return thisPoints;
    }

    inline double TwoPointLineNodeData::getLineWidth() const {
        return thisLineWidth;
    }

    inline QColor TwoPointLineNodeData::getLineColor() const {
        return thisLineColor;
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/









