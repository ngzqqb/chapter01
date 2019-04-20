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
            thisData->isChanged<TwoPointLineNodeState::PointChanged>()) {
            this->markDirty(DirtyGeometry);
            this->updateTheGeometry();
        }

        if (thisData->isChanged<TwoPointLineNodeState::LineColorChanged>()) {
            this->markDirty(DirtyMaterial);
            thisMaterial.setColor(thisData->getLineColor());
        }

        thisData->clearAllChanged();

    }

    void TwoPointLineNode::updateTheGeometry() {

        constexpr const auto varEpsilon =
            static_cast<qreal>(std::numeric_limits<GLfloat>::epsilon());

        const auto varTwoPoint = thisData->getTwoPoint();
        const auto varLineWidth = thisData->getLineWidth();

        auto varEndPoint = varTwoPoint.getSecondPoint();
        auto varStartPoint = varTwoPoint.getFirstPoint();

        auto dx = varEndPoint.x() - varStartPoint.x();
        auto dy = varEndPoint.y() - varStartPoint.y();

        auto varLength = std::hypot(dx, dy);

        /*检查数学库，有些编译器自身有bug*/
        assert(std::hypot(3., 4.) == 5.);

        /*检查是不是零长度直线*/
        if ((varLength < varEpsilon) || (varLineWidth < varEpsilon)) {

            auto varPoint = thisGeometry.vertexDataAsPoint2D();
            varPoint[0].set(0, 0);
            varPoint[1].set(0, 0);
            varPoint[2].set(0, 0);
            varPoint[3].set(0, 0);
            return;

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

        auto varPoint = thisGeometry.vertexDataAsPoint2D();
        varPoint[0].set(
            static_cast<GLfloat>(varStartPoint.x() - dy),
            static_cast<GLfloat>(varStartPoint.y() + dx));
        varPoint[1].set(
            static_cast<GLfloat>(varStartPoint.x() + dy),
            static_cast<GLfloat>(varStartPoint.y() - dx));
        varPoint[3].set(
            static_cast<GLfloat>(varEndPoint.x() + dy),
            static_cast<GLfloat>(varEndPoint.y() - dx));
        varPoint[2].set(
            static_cast<GLfloat>(varEndPoint.x() - dy),
            static_cast<GLfloat>(varEndPoint.y() + dx));

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
        thisState.setAll();
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/

