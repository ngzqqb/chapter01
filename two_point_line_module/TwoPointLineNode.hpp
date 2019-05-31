#pragma once

#include <sstd_qt_qml_quick_library.hpp>
#include "TwoPoint.hpp"

namespace sstd {

    enum class TwoPointLineNodeState : std::size_t {
        PointChanged,
        LineWidthChanged,
        LineColorChanged,
        WidthChanged,
        HeightChanged,
        Size
    };

    class TwoPointLineNodeData {
    public:
        TwoPointLineNodeData();
    public:
        inline TwoPoint getTwoPoint() const;
        inline double getLineWidth() const;
        inline QColor getLineColor() const;
        inline double getWidth() const;
        inline double getHeight() const;
    public:
        bool setTwoPoint(const TwoPoint &);
        bool setLineWidth(const double &);
        bool setLineColor(const QColor &);
        bool setWidth(const double &);
        bool setHeight(const double &);
    public:
        template<TwoPointLineNodeState>
        inline bool isChanged() const;
        inline void clearAllChanged();
    private:
        TwoPoint thisPoints;
        double thisLineWidth;
        double thisItemWidth;
        double thisItemHeight;
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
    private:
        void updateTheGeometry();
    public:
        void updateTheNode();
    private:
        std::shared_ptr<TwoPointLineNodeData> thisData;
        QSGFlatColorMaterial thisMaterial;
        QSGGeometry thisGeometry;
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

    inline double TwoPointLineNodeData::getWidth() const {
        return thisItemWidth;
    }

    inline double TwoPointLineNodeData::getHeight() const{
        return thisItemHeight;
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
