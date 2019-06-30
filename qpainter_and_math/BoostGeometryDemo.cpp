#include "BoostGeometryDemo.hpp"
#include <sstd/boost/geometry.hpp>

namespace sstd {

    BoostGeometryDemo::BoostGeometryDemo()
        : SubWindowBasic(QStringLiteral("BoostGeometryDemo")) {

        namespace bg = boost::geometry;
        using Point = bg::model::d2::point_xy<float>;
        using Polygon = bg::model::polygon<Point,false>;

        Polygon varPolygon{ {
            Point{0,0},
            Point{222,0},
            Point{222,222},
            Point{0,222}
        } };

        Polygon varHole{ {
            Point{70,70},
            Point{140,70},
            Point{140,140},
            Point{70,140}
        } };
       
       std::vector< Polygon > varAns;
       bg::difference(varPolygon,varHole,varAns);

       qDebug() << varAns.size() << ",";
        qDebug() << varAns[0].inners().size() << ",";
        qDebug() << bg::area(varPolygon);
        qDebug() << bg::area(varHole);
        qDebug() << bg::area(varAns[0]);
    }

}/*namespace sstd*/

// intersection : 
// https://www.boost.org/doc/libs/1_64_0/libs/geometry/doc/html/geometry/reference/algorithms/intersection/intersection_3.html
// algorithm : 
// https://www.boost.org/doc/libs/1_65_1/libs/geometry/doc/html/geometry/reference/algorithms.html

