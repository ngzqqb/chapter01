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
        width : parent.width
        height : parent.height

        twoPoint: Static.createTwoPoint(1,-1,-1,1)
        lineColor: "blue"
        lineWidth: 5

        transformOrigin : Item.Center

        SequentialAnimation on lineColor {
            id : idAnimationColor
            loops: 1
            ColorAnimation{ to : "yellow" ; duration: 5000}
            ColorAnimation{ to : "blue" ;duration: 5000}
        }

        Component.onDestruction: {
            idAnimationColor.stop();
        }

    }

    TwoPointLine {
        anchors.centerIn: parent
        width : parent.width
        height : parent.height

        twoPoint: Static.createTwoPoint(-1,-1,1,1)
        lineColor: Qt.rgba(1,0.2,0.2,1)
        lineWidth: 5

        transformOrigin : Item.Center

        SequentialAnimation on rotation {
            id : idAnimation
            loops: 1
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
