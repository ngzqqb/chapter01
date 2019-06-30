#include "TrianglePolygon.hpp"

#include <sstd/boost/polygon/polygon.hpp>
#include <sstd/boost/polygon/voronoi.hpp>

namespace sstd {

    using Polygon = boost::polygon::polygon_data< float >;
    using Point = boost::polygon::polygon_traits< Polygon >::point_type/*点*/;

    TrianglePolygon::TrianglePolygon()
        :SubWindowBasic(QStringLiteral("TrianglePolygon")) {

        auto varScene = this->scene();

        const std::array varPoints{
            Point{0,0},
            Point{100,-100},
            Point{150,50},
            Point{100,100},
            Point{0,100}
        };

        /*绘制点*/
        for (const auto & varI : varPoints) {
            varScene->addEllipse(varI.x() - 5, varI.y() - 5, 10, 10, 
                QPen{ QColor{},1 }, QBrush{ QColor{} });
        }

        /*进行三角形剖分*/
        boost::polygon::voronoi_diagram<double> varVoronoiDiagram;
        boost::polygon::construct_voronoi(
            varPoints.begin(),
            varPoints.end(),
            &varVoronoiDiagram);

        /*绘制边界*/
        auto & varEdges = varVoronoiDiagram.edges();
        for (const auto & varI : varEdges) {

            if (varI.is_finite()) {
                auto varV0 = varI.vertex0();
                auto varV1 = varI.vertex1();
                varScene->addLine({ {varV0->x(),varV0->y()},{varV1->x(),varV1->y()} },
                    QPen{ QColor(64,22,22),2 });
            } else if (varI.vertex0()) {

                const auto & varCell1 = varI.cell();
                const auto & varCell2 = varI.twin()->cell();

                auto varPoint0 = varPoints[varCell1->source_index()];
                auto varPoint1 = varPoints[varCell2->source_index()];

                auto varX = 0.5*(varPoint1.x() + varPoint0.x());
                auto varY = 0.5*(varPoint1.y() + varPoint0.y());

                auto varV0 = varI.vertex0();
                varScene->addLine({
                    { varV0->x(),varV0->y() },
                    { varV0->x() + 3 * (varX - varV0->x()),
                      varV0->y() + 3 * (varY - varV0->y()) }
                    }, QPen{ QColor(64,22,22),2 });

            }

        }

    }

}/*namespace sstd*/

// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/voronoi_basic_tutorial.htm
// voronoi_basic_tutorial.cpp
// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/gtl_segment_concept.htm

