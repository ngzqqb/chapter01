#include "DrawCircleByThreePoint.hpp"
#include <CGAL/Exact_circular_kernel_2.h>

namespace sstd {

    extern QGraphicsEllipseItem * drawCircleByThreePoint(QGraphicsScene * argScene,
        const QPointF & argP0,
        const QPointF & argP1,
        const QPointF & argP2,
        const QPen & argPen,
        const QBrush & argBrush) {

        using Circular_k = CGAL::Exact_circular_kernel_2;
        using Circular_arc_2 = CGAL::Circular_arc_2<Circular_k>;

        const Circular_arc_2 varCircle(
            { argP0.x(),argP0.y() },
            { argP1.x(),argP1.y() },
            { argP2.x(),argP2.y() });

        const auto & varCenterPoint = varCircle.center();
        const auto varRadius =
            std::sqrt(varCircle.squared_radius().to_double());
        const auto varDoubleRadius = 2 * varRadius;

        return argScene->addEllipse(QRectF{
            varCenterPoint.x().to_double() - varRadius,
            varCenterPoint.y().to_double() - varRadius,
            varDoubleRadius ,
            varDoubleRadius }, argPen, argBrush);

    }

}/*namespace sstd*/
