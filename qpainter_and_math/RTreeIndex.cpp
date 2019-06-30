#include "RTreeIndex.hpp"
#include <sstd/boost/geometry/index/rtree.hpp>

namespace sstd {

    template<typename T, typename A, typename B>
    inline static auto drawPoint(T * argScene,
        const A & argX, const B & argY,
        const QPen & argPen = {},
        const QBrush &argBrush = {}) {
        return argScene->addEllipse(argX - 5, argY - 5,
            10, 10,
            argPen, argBrush);
    }


    const QColor globalUnSelectColor{ 122,255,122 };
    const QColor globalSelectColor{ 122,255,255 };

    RTreeIndex::RTreeIndex() :
        SubWindowBasic(QStringLiteral("RTreeIndex")) {

        auto varScene = this->scene();

        namespace bg = boost::geometry;
        namespace bgi = boost::geometry::index;

        using Point = bg::model::point<double, 2, bg::cs::cartesian>;
        using Box = bg::model::box<Point>;
        using KeyValue = std::pair<Box, QGraphicsEllipseItem * >;
        using RTree = bgi::rtree< KeyValue, bgi::quadratic<16> >;

        RTree varRTree;

        for (int varI = 0; varI < 10; ++varI) {
            for (int varJ = 0; varJ < 10; ++varJ) {

                auto varX = varI * 15;
                auto varY = varJ * 15;
                auto varItem = drawPoint(varScene, varX, varY, globalUnSelectColor, globalUnSelectColor);
                auto varBoundRect = varItem->boundingRect();

                {
                    auto varTopLeft = varBoundRect.topLeft();
                    auto varBottomRight = varBoundRect.bottomRight();
                    varRTree.insert(KeyValue{ Box{ Point{varTopLeft.x(),varTopLeft.y()},
                                                Point{varBottomRight.x(),varBottomRight.y()} } ,
                                                varItem });
                }

            }
        }

        Box varSelectBox{ {10,10},{50,50} };
        varScene->addRect( 10 , 10 , 40 , 40  );

        std::vector< KeyValue > varAns;
        varRTree.query(bgi::intersects(varSelectBox), std::back_inserter(varAns));
        for (auto & varI : varAns) {
            varI.second->setBrush( globalSelectColor );
            varI.second->setPen(globalSelectColor);
        }

    }

}/*namespace sstd*/


// https://www.boost.org/doc/libs/1_63_0/libs/geometry/doc/html/geometry/spatial_indexes/rtree_examples/quick_start.html






