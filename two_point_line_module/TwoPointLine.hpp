﻿/* two_point_line_module/TwoPointLine.hpp */
#pragma once

#include <bitset>
#include "TwoPoint.hpp"
#include "TwoPointLineNode.hpp"
#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class TwoLineNode;
    class TwoPointLine : public QQuickItem {
        Q_OBJECT
    private:
        using Super = QQuickItem;
    public:
        Q_PROPERTY(QVariant twoPoint READ getTwoPoint WRITE setTwoPoint NOTIFY twoPointChanged)
    public:
        Q_PROPERTY(double lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    public:
        Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged)
    public:
        TwoPointLine(QQuickItem*parent = nullptr);
        ~TwoPointLine();
    protected:
        virtual void componentComplete() override;
    public:
        inline QVariant getTwoPoint() const;
        void setTwoPoint(const QVariant &varTwoPoint);
        Q_SIGNAL void twoPointChanged();
    public:
        inline double getLineWidth() const;
        void setLineWidth(const double &varLineWidth);
        Q_SIGNAL void lineWidthChanged();
    public:
        inline QColor getLineColor() const;
        void setLineColor(const QColor &varLineColor);
        Q_SIGNAL void lineColorChanged();
    protected:
        virtual QSGNode * updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *) override;
    private:
        friend class TwoLineNode;
    private:
        std::shared_ptr< TwoPointLineNodeData > thisNodeData ;
    private:
        sstd_class(TwoPointLine);
    };

    inline QVariant TwoPointLine::getTwoPoint() const {
        return QVariant::fromValue(thisNodeData->getTwoPoint());
    }

    inline double TwoPointLine::getLineWidth() const {
        return thisNodeData->getLineWidth();
    }

    inline QColor TwoPointLine::getLineColor() const {
        return thisNodeData->getLineColor();
    }

}/*namespace sstd*/
