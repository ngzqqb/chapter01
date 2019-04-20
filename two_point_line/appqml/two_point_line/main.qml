/* appqml/two_point_line/main.qml */
import QtQuick 2.9
import QtQuick.Controls 2.5

/*begin:import*/
import theqml_the_debug.two_point_line_module 1.0
/*end:import*/

ApplicationWindow {

    width: 360 ;
    height: 64 ;
    visible: true ;

    TwoPointLine {
        anchors.fill: parent;

        twoPoint: Static.createTwoPoint(0,0,100,100)
        lineColor: Qt.rgba(1,0.2,0.2,1)
        lineWidth: 5

    }

}
/*endl_input_of_latex_for_clanguage_lick*/
/*begin:debug*/
/*end:debug*/
