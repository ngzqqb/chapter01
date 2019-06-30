#include "RTreeIndex.hpp"
#include <sstd/boost/geometry.hpp>
#include <sstd/boost/geometry/index/rtree.hpp>

namespace sstd {

    template<typename T, typename A, typename B>
    inline static auto drawRect(T * argScene,
        const A & argX, const B & argY,
        const QPen & argPen = {},
        const QBrush &argBrush = {}) {
        return argScene->addRect(argX - 5, argY - 5,
            10, 10,
            argPen, argBrush);
    }

    template<typename T>
    inline static QPolygonF toQPolygon(const T & arg) {
        QVector< QPointF > varPoints;
        for (const auto & varI : arg) {
            varPoints.push_back({ varI.get<0>() ,varI.get<1>() });
        }
        return { std::move(varPoints) };
    }

    const QColor globalUnSelectColor{ 122,255,122 };
    const QColor globalSelectColor{ 255,122,122 };

    RTreeIndex::RTreeIndex() :
        SubWindowBasic(QStringLiteral("RTreeIndex")) {

        auto varScene = this->scene();

        namespace bg = boost::geometry;
        namespace bgi = boost::geometry::index;

        using Point = bg::model::point<double, 2, bg::cs::cartesian>;
        using Box = bg::model::box<Point>;
        using KeyValue = std::pair<Box, QGraphicsRectItem * >;
        using RTree = bgi::rtree< KeyValue, bgi::rstar<16> >;

        RTree varRTree;

        for (int varI = 0; varI < 10; ++varI) {
            for (int varJ = 0; varJ < 10; ++varJ) {

                auto varX = varI * 15;
                auto varY = varJ * 15;
                auto varItem = drawRect(varScene, varX, varY, globalUnSelectColor, globalUnSelectColor);
                auto varBoundRect = varItem->boundingRect();

                {
                    auto varTopLeft = varBoundRect.topLeft();
                    auto varBottomRight = varBoundRect.bottomRight();
                    varRTree.insert(KeyValue{ Box{
                        Point{varTopLeft.x(),varTopLeft.y()},
                        Point{varBottomRight.x(),varBottomRight.y()}
                        } , varItem });
                }

            }
        }

        const bg::model::polygon< Point, false, false > varSelectPolygon{ {
            Point{10,10},
            Point{50,15},
            Point{55,75},
            Point{15,65}
            } };
        varScene->addPolygon(toQPolygon(varSelectPolygon.outer()));

        std::vector< KeyValue > varAns;
        varRTree.query(bgi::intersects(varSelectPolygon), std::back_inserter(varAns));
        for (auto & varI : varAns) {
            varI.second->setBrush(globalSelectColor);
            varI.second->setPen(globalSelectColor);
        }
        qDebug() << varAns.size();

    }

}/*namespace sstd*/


// https://www.boost.org/doc/libs/1_63_0/libs/geometry/doc/html/geometry/spatial_indexes/rtree_examples/quick_start.html






