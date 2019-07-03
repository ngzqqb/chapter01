#pragma once

#include "SubWindowBasic.hpp"
#include <set>

namespace sstd {

    class ConnectVisibleNodeLine;

    class VisibleNodeItem :
        public QObject,
        public QGraphicsEllipseItem {
        Q_OBJECT
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

    class ConnectVisibleNodeLine :
        public QObject,
        public QGraphicsLineItem {
        Q_OBJECT
    public:
        ConnectVisibleNodeLine(VisibleNodeItem*, VisibleNodeItem*);
        void visibleItemChanged();
    private:
        VisibleNodeItem * thisLine0{ nullptr };
        VisibleNodeItem * thisLine1{ nullptr };
    private:
        sstd_class(ConnectVisibleNodeLine);
    };

    class BoostGraphDemo :
        public SubWindowBasic {
        Q_OBJECT
    public:
        BoostGraphDemo();
    private:
        sstd_class(BoostGraphDemo);
    };


}/*namespace sstd*/




