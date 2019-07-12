#pragma once

#include "SubWindowBasic.hpp"
#include <set>

namespace sstd {

    class ConnectVisibleNodeLine;

    class VisibleNodeItem final :
        public QGraphicsEllipseItem {
    public:
        VisibleNodeItem(const QString &, const qreal &, const qreal &);
        void attacheLine(ConnectVisibleNodeLine *);
    private:
        std::set<ConnectVisibleNodeLine * > thisLines;
        void updatePos(ConnectVisibleNodeLine *);
    protected:
        QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    private:
        sstd_class(VisibleNodeItem);
    };

    class ConnectVisibleNodeLine final :
        public QGraphicsLineItem {
    public:
        ConnectVisibleNodeLine(VisibleNodeItem*, VisibleNodeItem*);
        void visibleItemChanged();
    private:
        VisibleNodeItem * thisLine0{ nullptr };
        VisibleNodeItem * thisLine1{ nullptr };
    private:
        sstd_class(ConnectVisibleNodeLine);
    };

    class BoostGraphDemo final:
        public SubWindowBasic {
        Q_OBJECT
    public:
        BoostGraphDemo();
    private:
        sstd_class(BoostGraphDemo);
    };


}/*namespace sstd*/




