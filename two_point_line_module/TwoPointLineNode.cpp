#include "TwoPointLineNode.hpp"

namespace sstd {

    bool TwoPointLineNodeData::setTwoPoint(const TwoPoint & arg) {
        if (arg == thisPoints) {
            return false;
        }
        thisPoints = arg;
        thisState.set<TwoPointLineNodeState::PointChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setLineWidth(const double & arg) {
        if (arg == thisLineWidth) {
            return false;
        }
        thisLineWidth = arg;
        thisState.set<TwoPointLineNodeState::LineWidthChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setWidth(const double & arg) {
        if (arg == thisItemWidth) {
            return false;
        }
        thisItemWidth = arg;
        thisState.set<TwoPointLineNodeState::WidthChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setHeight(const double & arg) {
        if (arg == thisItemHeight) {
            return false;
        }
        thisItemHeight = arg;
        thisState.set<TwoPointLineNodeState::HeightChanged>();
        return true;
    }

    bool TwoPointLineNodeData::setLineColor(const QColor & arg) {
        if (arg == thisLineColor) {
            return false;
        }
        thisLineColor = arg;
        thisState.set<TwoPointLineNodeState::LineColorChanged>();
        return true;
    }

    void TwoPointLineNode::updateTheNode() {

        if (thisData->isChanged<TwoPointLineNodeState::LineWidthChanged>() ||
            thisData->isChanged<TwoPointLineNodeState::PointChanged>() ||
            thisData->isChanged<TwoPointLineNodeState::WidthChanged>() ||
            thisData->isChanged<TwoPointLineNodeState::HeightChanged>()) {
            this->markDirty(DirtyGeometry);
            this->updateTheGeometry();
        }

        if (thisData->isChanged<TwoPointLineNodeState::LineColorChanged>()) {
            this->markDirty(DirtyMaterial);
            thisMaterial.setColor(thisData->getLineColor());
        }

        thisData->clearAllChanged();

    }

    inline static std::array< QPointF, 4 > updateGeometryByTwoPoints(QPointF varStartPoint,
        QPointF varEndPoint,
        double varLineWidth,
        bool & argIsEmpty) {

        constexpr const auto varEpsilon =
            static_cast<qreal>(std::numeric_limits<GLfloat>::epsilon());

        argIsEmpty = false;
        auto dx = varEndPoint.x() - varStartPoint.x();
        auto dy = varEndPoint.y() - varStartPoint.y();

        auto varLength = std::hypot(dx, dy);

        /*检查数学库，有些编译器自身有bug*/
        assert(std::hypot(3., 4.) == 5.);

        /*检查是不是零长度直线*/
        if ((varLength < varEpsilon) || (varLineWidth < varEpsilon)) {
            argIsEmpty = true;
            return {};
        }

        /*调整点环绕方向*/
        if (dx < 0) {
            dx *= -1;
            dy *= -1;
            std::swap(varStartPoint, varEndPoint);
        }

        /*计算矩形的四个点*/
        varLength = 0.5 * varLineWidth / varLength;
        dx *= varLength;
        dy *= varLength;

        return { QPointF{ varStartPoint.x() - dy,varStartPoint.y() + dx },
            QPointF{ varStartPoint.x() + dy,varStartPoint.y() - dx },
            QPointF{ varEndPoint.x() - dy,varEndPoint.y() + dx },
            QPointF{ varEndPoint.x() + dy,varEndPoint.y() - dx } };

    }

    inline static std::array< QPointF, 4 > updateGeometryByTwoPoints(const QPointF & varStartPoint,
        const QPointF & varEndPoint,
        double argScaleX,
        double argScaleY,
        double varLineWidth,
        bool & argIsEmpty) {

        argScaleX *= 0.5;
        argScaleY *= 0.5;

        return updateGeometryByTwoPoints(
            { std::fma(argScaleX , varStartPoint.x() , argScaleX),std::fma(argScaleY , varStartPoint.y(),argScaleY) },
            { std::fma(argScaleX , varEndPoint.x() , argScaleX),std::fma(argScaleY , varEndPoint.y(),argScaleY) },
            varLineWidth,
            argIsEmpty);
    }

    void TwoPointLineNode::updateTheGeometry() {

        const auto varTwoPoint = thisData->getTwoPoint();
        const auto varLineWidth = thisData->getLineWidth();
        bool varIsEmpty{ false };

        auto varPoints = updateGeometryByTwoPoints(
            varTwoPoint.getFirstPoint(),
            varTwoPoint.getSecondPoint(),
            thisData->getWidth(),
            thisData->getHeight(),
            varLineWidth,
            varIsEmpty);

        auto varPoint = thisGeometry.vertexDataAsPoint2D();

        /*检查是不是零长度直线*/
        if (varIsEmpty) {
            varPoint[0].set(0, 0);
            varPoint[1].set(0, 0);
            varPoint[2].set(0, 0);
            varPoint[3].set(0, 0);
            return;
        } else {
            varPoint[0].set(
                static_cast<GLfloat>(varPoints[0].x()),
                static_cast<GLfloat>(varPoints[0].y()));
            varPoint[1].set(
                static_cast<GLfloat>(varPoints[1].x()),
                static_cast<GLfloat>(varPoints[1].y()));
            varPoint[2].set(
                static_cast<GLfloat>(varPoints[2].x()),
                static_cast<GLfloat>(varPoints[2].y()));
            varPoint[3].set(
                static_cast<GLfloat>(varPoints[3].x()),
                static_cast<GLfloat>(varPoints[3].y()));
        }

    }

    TwoPointLineNode::TwoPointLineNode(std::shared_ptr<TwoPointLineNodeData> arg) :
        thisData{ std::move(arg) },
        thisGeometry{ QSGGeometry::defaultAttributes_Point2D(), 4 }{
        this->setMaterial(&thisMaterial);
        this->setGeometry(&thisGeometry);
        thisGeometry.setDrawingMode(QSGGeometry::DrawTriangleStrip);
    }

    TwoPointLineNodeData::TwoPointLineNodeData() {
        thisLineWidth = 1;
        thisItemWidth = 0;
        thisItemHeight = 0;
        thisState.setAll();
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/

