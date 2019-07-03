#include "NearestPoint.hpp"

#include <sstd/boost/geometry.hpp>
#include <sstd/boost/geometry/index/rtree.hpp>

namespace sstd {

    template<typename T, typename A, typename B>
    inline static auto drawPoint(T * argScene,
        const A & argX, const B & argY,
        const QPen & argPen = {},
        const QBrush &argBrush = {}) {
        auto varAns = argScene->addEllipse(-5, -5,
            10, 10,
            argPen, argBrush);
        varAns->setPos(argX, argY);
        return varAns;
    }

    template<typename T>
    inline static QPolygonF toQPolygon(const T & arg) {
        QVector< QPointF > varPoints;
        for (const auto & varI : arg) {
            varPoints.push_back({ varI.template get<0>() ,varI.template get<1>() });
        }
        return { std::move(varPoints) };
    }

    const QColor globalUnSelectColor{ 122,255,122 };
    const QColor globalSelectColor{ 255,122,122 };

    NearestPoint::NearestPoint()
        : SubWindowBasic(QStringLiteral("NearestPoint")) {

        auto varScene = this->scene();

        namespace bg = boost::geometry;
        namespace bgi = boost::geometry::index;

        using Point = bg::model::point<double, 2, bg::cs::cartesian>;
        using KeyValue = std::pair<Point, QAbstractGraphicsShapeItem * >;
        using RTree = bgi::rtree< KeyValue, bgi::rstar<16> >;

        RTree varRTree;

        for (int varI = 0; varI < 10; ++varI) {
            for (int varJ = 0; varJ < 10; ++varJ) {
                auto varX = varI * 15;
                auto varY = varJ * 15;
                auto varItem = drawPoint(varScene, varX, varY, globalUnSelectColor, globalUnSelectColor);
                varRTree.insert(KeyValue{ Point(varX,varY) , varItem });
            }
        }

        const QPointF varPoint{ 52,75 };
        varScene->addEllipse(-3, -3, 6, 6, {}, QColor{0,0,0})->setPos(varPoint);

        {
            auto varAns = varRTree.qbegin(bgi::nearest(Point{ varPoint.x(),varPoint.y() }, 8));
            auto varAnsEnd = varRTree.qend();
            int varIndex{ 0 };
            for (;varAns!=varAnsEnd;++varAns) {
                auto & varI = *varAns;
                varI.second->setBrush(globalSelectColor);
                varI.second->setPen(globalSelectColor);
                varI.second->setZValue(100-varIndex);
                auto varText = varScene->addText(QString::number(++varIndex));
                varText->setParentItem(varI.second);
                varText->setPos(-varText->boundingRect().center());
            }
        }

    }

}/*namespace sstd*/


