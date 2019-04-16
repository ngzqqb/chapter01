/* two_point_line_module/TwoPointLine.hpp */
#pragma once

#include "TwoPoint.hpp"
#include <sstd_qt_qml_quick_library.hpp>

namespace sstd{

    class TwoPointLine : public QQuickItem {
        Q_OBJECT
    private:
        using Super = QQuickItem;
    public:
        Q_PROPERTY(TwoPoint twoPoint READ getTwoPoint WRITE setTwoPoint NOTIFY twoPointChanged)
    public:
        Q_PROPERTY(double lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    public:
        Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged)
    public:
        TwoPointLine(QQuickItem*parent=nullptr);
    public:
        inline TwoPoint getTwoPoint() const;
        void setTwoPoint(const TwoPoint &);
        Q_SIGNAL void twoPointChanged();
    public:
        inline double getLineWidth() const;
        void setLineWidth(const double &);
        Q_SIGNAL void lineWidthChanged();
    public:
        inline QColor getLineColor() const;
        void setLineColor(const QColor &);
        Q_SIGNAL void lineColorChanged();
    private:
        TwoPoint thisData;
        double thisLineWidth;
        QColor thisLineColor;
    private:
        sstd_class(TwoPointLine);
    };

    inline TwoPoint TwoPointLine::getTwoPoint() const{
        return thisData;
    }

    inline double TwoPointLine::getLineWidth() const{
        return thisLineWidth;
    }

    inline QColor TwoPointLine::getLineColor() const{
        return thisLineColor;
    }

}/*namespace sstd*/


