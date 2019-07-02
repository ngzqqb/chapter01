#include "CGALDemo.hpp"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Polygon_2.h>

namespace sstd {

    template<typename B, typename E>
    inline static auto drawPolygon(QGraphicsScene * argScene,
        B argPos, const E argEnd,
        const QPen & argPen = {},
        const QBrush & argBrush = {}) {
        QVector<QPointF> varPoints;
        for (; argPos != argEnd; ++argPos) {
            varPoints.push_back({ argPos->x(),argPos->y() });
        }
        return argScene->addPolygon({ std::move(varPoints) },
            argPen, argBrush);
    }

    inline const QColor globalPolygonBoundColor{ 200,10,10 };

    class FaceInfo2 {
    public:
        inline FaceInfo2() {
        }
        int nesting_level{ 0 };
        inline bool in_domain() const {
            return (nesting_level & 1) == 1;
        }
    private:
        sstd_class(FaceInfo2);
    };

    using K = CGAL::Exact_predicates_inexact_constructions_kernel;
    using Vb = CGAL::Triangulation_vertex_base_2<K>;
    using Fbb = CGAL::Triangulation_face_base_with_info_2<FaceInfo2, K>;
    using Fb = CGAL::Constrained_triangulation_face_base_2<K, Fbb>;
    using TDS = CGAL::Triangulation_data_structure_2<Vb, Fb>;
    using Itag = CGAL::Exact_predicates_tag;
    using CDT = CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>;
    using Point = CDT::Point;
    using Polygon_2 = CGAL::Polygon_2<K>;

    CGALDemo::CGALDemo() :
        SubWindowBasic(QStringLiteral("CGALDemo")) {

        auto varScene = this->scene();

        CDT varCDT;

        /*准备数据 ... */
        Polygon_2 polygon1;
        polygon1.push_back(Point(0, 0));
        polygon1.push_back(Point(100, -50));
        polygon1.push_back(Point(200, 0));
        polygon1.push_back(Point(200, 200));
        polygon1.push_back(Point(0, 200));

        Polygon_2 polygon2;
        polygon2.push_back(Point(50, 50));
        polygon2.push_back(Point(150, 50));
        polygon2.push_back(Point(150, 150));
        polygon2.push_back(Point(50, 150));

        /*绘制多边形边界 ... */
        drawPolygon(varScene,
            polygon1.vertices_begin(), polygon1.vertices_end(),
            globalPolygonBoundColor)->setZValue(100);
        drawPolygon(varScene,
            polygon2.vertices_begin(), polygon2.vertices_end(),
            globalPolygonBoundColor)->setZValue(100);

        CDT cdt;
        cdt.insert_constraint(polygon1.vertices_begin(), polygon1.vertices_end(),
            true/*要求闭合曲线*/);
        cdt.insert_constraint(polygon2.vertices_begin(), polygon2.vertices_end(),
            true/*要求闭合曲线*/);

        auto varFace = cdt.finite_faces_begin();
        const auto varFaceEnd = cdt.finite_faces_end();

        std::array< QPointF, 3 > varTriangle;
        for (; varFace != varFaceEnd; ++varFace) {

            varFace->info().nesting_level = varFace->is_constrained(0)
                + varFace->is_constrained(1) + 
                varFace->is_constrained(2);

            if (!varFace->info().in_domain()) {
                continue;
            }
            for (int varI = 0; varI < 3; ++varI) {
                const auto & varPoint = varFace->vertex(varI)->point();
                varTriangle[varI].setX(varPoint.x());
                varTriangle[varI].setY(varPoint.y());
            }
            drawPolygon(varScene, varTriangle.begin(), varTriangle.end(), 
                { QColor{},2 }, QColor{ 200,200,200 });
        }

    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://doc.cgal.org/latest/Triangulation_2/
