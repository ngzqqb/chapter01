#include "CGALDemo.hpp"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Polygon_2.h>
#include "DrawCircleByThreePoint.hpp"

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
            return (nesting_level & 1) != 0;
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

    inline void mark_domains(CDT& ct,
        CDT::Face_handle start,
        int index,
        std::list<CDT::Edge>& border) {
        if (start->info().nesting_level != -1) {
            return;
        }
        std::list<CDT::Face_handle> queue;
        queue.push_back(start);
        while (!queue.empty()) {
            CDT::Face_handle fh = queue.front();
            queue.pop_front();
            if (fh->info().nesting_level == -1) {
                fh->info().nesting_level = index;
                for (int i = 0; i < 3; ++i) {
                    CDT::Edge e(fh, i);
                    CDT::Face_handle n = fh->neighbor(i);
                    if (n->info().nesting_level == -1) {
                        if (ct.is_constrained(e)) {
                            border.push_back(e);
                        } else {
                            queue.push_back(n);
                        }
                    }
                }
            }
        }
    }

    /*
    1.将所有三角形域标记为-1；
    2.将所有与非限定性边相邻的三角形域标记为0；
    3.如果一个标记为-1的域与一个标记为非-1的域相邻于限定性边，则非-1域+1；
    对于限定性三角形，nesting_level为偶数，则为外，为奇数则为内。
    */
    inline void mark_domains(CDT& cdt) {
        for (CDT::All_faces_iterator it = cdt.all_faces_begin();
            it != cdt.all_faces_end();
            ++it) {
            it->info().nesting_level = -1;
        }
        std::list<CDT::Edge> border;
        mark_domains(cdt, cdt.infinite_face(), 0, border);
        while (!border.empty()) {
            CDT::Edge e = border.front();
            border.pop_front();
            CDT::Face_handle n = e.first->neighbor(e.second);
            if (n->info().nesting_level == -1) {
                mark_domains(cdt, n, e.first->info().nesting_level + 1, border);
            }
        }
    }

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

        mark_domains(cdt);

        auto varFace = cdt.finite_faces_begin();
        const auto varFaceEnd = cdt.finite_faces_end();

        std::array< QPointF, 3 > varTriangle;
        for (; varFace != varFaceEnd; ++varFace) {

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
            drawCircleByThreePoint(varScene,
                varTriangle[0], varTriangle[1], varTriangle[2],
                { QColor{100,100,100},1.2 })
                ->setZValue(998);
        }

    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://doc.cgal.org/latest/Triangulation_2/
// https://doc.cgal.org/latest/Triangulation_2/classCGAL_1_1Constrained__triangulation__2.html
// https://doc.cgal.org/latest/Circular_kernel_2/index.html
