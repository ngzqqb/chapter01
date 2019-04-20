/* appqml/two_point_line/main.qml */
import QtQuick 2.9
import QtQuick.Controls 2.5

/*begin:import*/
import theqml_the_debug.two_point_line_module 1.0
/*end:import*/

ApplicationWindow {

    width: 200 ;
    height: 200 ;
    visible: true ;

    TwoPointLine {
        anchors.centerIn: parent

        twoPoint: Static.createTwoPoint(0,0,200,200)
        lineColor: "blue"
        lineWidth: 5

        onTwoPointChanged: {
            var varFirst = twoPoint.getFirstPoint();
            var varSecond = twoPoint.getSecondPoint();
            width = Math.abs( varFirst.x - varSecond.x );
            height = Math.abs( varFirst.y - varSecond.y );
        }

        transformOrigin : Item.Center

        SequentialAnimation on lineColor {
            id : idAnimationColor
            loops: Animation.Infinite
            ColorAnimation{ to : "yellow" ; duration: 5000}
            ColorAnimation{ to : "blue" ;duration: 5000}
        }

        Component.onDestruction: {
            idAnimationColor.stop();
        }

    }

    TwoPointLine {
        anchors.centerIn: parent

        twoPoint: Static.createTwoPoint(0,0,200,200)
        lineColor: Qt.rgba(1,0.2,0.2,1)
        lineWidth: 5

        onTwoPointChanged: {
            var varFirst = twoPoint.getFirstPoint();
            var varSecond = twoPoint.getSecondPoint();
            width = Math.abs( varFirst.x - varSecond.x );
            height = Math.abs( varFirst.y - varSecond.y );
        }

        transformOrigin : Item.Center

        SequentialAnimation on rotation {
            id : idAnimation
            loops: Animation.Infinite
            NumberAnimation{ to : 360 ; duration: 5000}
            NumberAnimation{ to : 0 ;duration: 5000}
        }

        Component.onDestruction: {
            idAnimation.stop();
        }

    }

}
/*endl_input_of_latex_for_clanguage_lick*/
/*begin:debug*/
/*end:debug*/
