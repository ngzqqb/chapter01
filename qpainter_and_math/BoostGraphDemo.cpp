#include "BoostGraphDemo.hpp"

namespace sstd {

    constexpr qreal globalVisibleNodeItemSize = 28;

    VisibleNodeItem::VisibleNodeItem(const QString & argText,
        const qreal & argX,
        const qreal & argY) :
        QGraphicsEllipseItem(-0.5*globalVisibleNodeItemSize,
            -0.5*globalVisibleNodeItemSize,
            globalVisibleNodeItemSize,
            globalVisibleNodeItemSize) {
        this->setPos(argX, argY);
        auto varText = sstd_virtual_new<QGraphicsTextItem>(argText);
        varText->setParentItem(this);
        varText->setPos(-varText->boundingRect().center());
        this->setFlag(ItemIsMovable);
        this->setFlag(ItemSendsGeometryChanges);
    }

    void VisibleNodeItem::updatePos(ConnectVisibleNodeLine * arg) {
        arg->visibleItemChanged();
    }

    void VisibleNodeItem::attacheLine(ConnectVisibleNodeLine * arg) {
        if (arg&&thisLines.insert(arg).second) {
            updatePos(arg);
        }
    }

    QVariant VisibleNodeItem::itemChange(
        QGraphicsItem::GraphicsItemChange change,
        const QVariant &value) {
        if ((ItemPositionChange == change) && scene()) {
            for (const auto & varI : thisLines) {
                updatePos(varI);
            }
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

    ConnectVisibleNodeLine::ConnectVisibleNodeLine(VisibleNodeItem* argA,
        VisibleNodeItem* argB) {
        thisLine0 = argA;
        thisLine1 = argB;
        argA->attacheLine(this);
        argB->attacheLine(this);
    }

    void ConnectVisibleNodeLine::visibleItemChanged() {

        const constexpr QPointF varOffset{
            globalVisibleNodeItemSize*0.5,
            globalVisibleNodeItemSize*0.5
        };

        const auto var0 = thisLine0->pos();
        const auto var1 = thisLine1->pos();

        auto varDx = var0.x() - var1.x();
        auto varDy = var0.y() - var1.y();
        auto varLineLength = std::hypot(varDx, varDy);

        if (varLineLength <= std::numeric_limits<float>::epsilon()) {
            varDx = 1;
            varDy = 0;
        } else {
            varDx /= varLineLength;
            varDy /= varLineLength;
        }

        varDx *= globalVisibleNodeItemSize * 0.5;
        varDy *= globalVisibleNodeItemSize * 0.5;

        this->setLine(var0.x() - varDx, var0.y() - varDy,
            var1.x() + varDx, var1.y() + varDy);

    }

    BoostGraphDemo::BoostGraphDemo() :
        SubWindowBasic(QStringLiteral("BoostGraphDemo")) {

        auto varScene = this->scene();

        auto a = sstd_new< VisibleNodeItem>(QStringLiteral("B"), 0, 0);
        auto b = sstd_new< VisibleNodeItem>(QStringLiteral("A"), 25, 25);
        varScene->addItem(a);
        varScene->addItem(b);
        varScene->addItem(sstd_new<ConnectVisibleNodeLine>(a, b));

    }

}/*namespace sstd*/

























