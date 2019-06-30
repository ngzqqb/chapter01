#include "BoostGeometryDemo.hpp"
#include <sstd/boost/geometry.hpp>

namespace sstd {

    template<typename T>
    inline static QPolygonF toQPolygonF(const T & arg) {
        QVector<QPointF> varAns;
        for (const auto & varI : arg) {
            varAns.push_back({ varI.x(),varI.y() });
        }
        return { std::move(varAns) };
    }

    const static auto globalTheColor = QColor(255, 128, 255);

    BoostGeometryDemo::BoostGeometryDemo()
        : SubWindowBasic(QStringLiteral("BoostGeometryDemo")) {

        namespace bg = boost::geometry;
        using Point = bg::model::d2::point_xy<float>;
        using Polygon = bg::model::polygon<Point, false>;
        std::vector< Polygon > varAns;

        {
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
            bg::difference(varPolygon, varHole, varAns);
        }

        assert(varAns.size() == 1);
        assert(varAns[0].inners().size() == 1);

        QPainterPath varPath;
        varPath.addPolygon(toQPolygonF(varAns[0].outer()));
        varPath.addPolygon(toQPolygonF(varAns[0].inners()[0]));

        auto varScene = this->scene();

        auto varText = varScene->addText(tr(u8R"(面积 ： )") +
            QString::number(bg::area(varAns[0])));
        varText->setParentItem(
            varScene->addPath(varPath,
                QPen{ globalTheColor },
                QBrush{ globalTheColor })
        );
        auto varFont = varText->font();
        varFont.setPixelSize(16);
        varFont.setBold(true);
        varText->setFont(std::move(varFont));
    }

}/*namespace sstd*/

// intersection : 
// https://www.boost.org/doc/libs/1_64_0/libs/geometry/doc/html/geometry/reference/algorithms/intersection/intersection_3.html
// algorithm : 
// https://www.boost.org/doc/libs/1_65_1/libs/geometry/doc/html/geometry/reference/algorithms.html

