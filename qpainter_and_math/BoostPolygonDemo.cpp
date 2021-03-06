﻿#include "BoostPolygonDemo.hpp"
#include <sstd/boost/polygon/polygon.hpp>

namespace sstd {

    using Polygon = boost::polygon::polygon_data<float>;
    using Point = boost::polygon::polygon_traits< Polygon >::point_type/*点*/;

    template<typename T>
    inline static QPolygonF toQPolygon(const T & arg) {
        QVector< QPointF > varPoints;
        for (const auto & varI : arg) {
            varPoints.push_back({ varI.x() ,varI.y() });
        }
        return { std::move(varPoints) };
    }

    const static auto globalTheColor = QColor(1, 128, 255);

    BoostPolygonDemo::BoostPolygonDemo()
        : SubWindowBasic(QStringLiteral("BoostPolygonDemo")) {
        auto varScene = this->scene();
        Polygon varPolygon;

        {
            const std::array varPoints{
                Point{0,0},
                Point{100,0},
                Point{150,50},
                Point{100,100},
                Point{0,100}
            };
            varPolygon.set(varPoints.begin(), varPoints.end());
        }

        {/*与另一个多边形相加*/
            std::array varPoints{
                Point{-30,-10},
                Point{-10,50},
                Point{150,50},
            };
            Polygon varAdd;
            varAdd.set(varPoints.begin(), varPoints.end());
            std::vector < Polygon > varPolygonSet;
            using namespace boost::polygon::operators;
            varPolygonSet += std::move(varPolygon);
            varPolygonSet += std::move(varAdd);
            varPolygon = std::move(varPolygonSet[0]);
        }

        {/*获得外接矩形*/
            boost::polygon::rectangle_data<float>  varBoundRect;
            extents(varBoundRect, varPolygon);
            QPointF varPoint1, varPoint2;
            {
                auto varRectangleData = varBoundRect.get(boost::polygon::HORIZONTAL);
                varPoint1.setX(varRectangleData.low());
                varPoint2.setX(varRectangleData.high());
            }
            {
                auto varRectangleData = varBoundRect.get(boost::polygon::VERTICAL);
                varPoint1.setY(varRectangleData.low());
                varPoint2.setY(varRectangleData.high());
            }
            varScene->addRect({ varPoint1,varPoint2 }, QPen{ QColor(1,1,1) ,1.2f })
                ->setZValue(10);
        }

        /*计算面积并显示*/
        auto varText = varScene->addText(tr(u8R"(面积 ： )") +
            QString::number(area(varPolygon)));
        varText->setParentItem(
            varScene->addPolygon(toQPolygon(varPolygon),
                QPen{ globalTheColor },
                QBrush{ globalTheColor })
        );
        auto varFont = varText->font();
        varFont.setPixelSize(16);
        varFont.setBold(true);
        varText->setFont(std::move(varFont));
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/gtl_isotropy.htm
// https://www.youtube.com/watch?v=6MGLiIwc1_0
// https://www.boost.org/doc/libs/1_70_0/libs/polygon/doc/gtl_polygon_set_concept.htm
