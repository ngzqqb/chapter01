﻿#include "TrianglePolygon.hpp"

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
            Point{15,22},
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

        const QPen varBoundPen{ QColor(84,22,22),2 };
        /*绘制边界*/
        auto & varCells = varVoronoiDiagram.cells();
        for (const auto & varI : varCells) {
            auto varEdge = varI.incident_edge();
            do {
                if (varEdge->is_primary()) {
                    if (varEdge->is_finite()) {
                        if (varEdge->cell()->source_index() <
                            varEdge->twin()->cell()->source_index()) {
                            varScene->addLine({ 
                                { varEdge->vertex0()->x(), varEdge->vertex0()->y() },
                                { varEdge->vertex1()->x(), varEdge->vertex1()->y() } 
                                }, varBoundPen);
                        }
                    } else {
                        auto v0 = varEdge->vertex0();
                        if (v0) {
                            auto p1 = varPoints[varEdge->cell()->source_index()];
                            auto p2 = varPoints[varEdge->twin()->cell()->source_index()];
                            auto end_x = (p1.y() - p2.y()) * 8;
                            auto end_y = (p1.x() - p2.x()) * -8;
                            varScene->addLine({ {v0->x(), v0->y()},
                                {end_x, end_y} }, varBoundPen);
                        }
                    }
                }
                varEdge = varEdge->next();
            } while (varEdge != varI.incident_edge());
        }

    }

}/*namespace sstd*/

// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/voronoi_basic_tutorial.htm
// voronoi_basic_tutorial.cpp
// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/gtl_segment_concept.htm

