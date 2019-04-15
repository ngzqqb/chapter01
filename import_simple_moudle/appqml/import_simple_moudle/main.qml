﻿import QtQuick 2.9
import QtQuick.Controls 2.5

/*begin:import*/
import theqml_the_debug.simple_moudle 1.0
/*end:import*/

ApplicationWindow {

    width: 360 ;
    height: 64 ;
    visible: true ;

    Text {
        text: qsTr("你好世界！");
        SomeData{
            id:idRandomColor
        }
        color: idRandomColor.getRandomColor();
        font.pointSize: 32;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        anchors.centerIn: parent;
        Timer{
            interval: 1236;
            running: true;
            repeat: true;
            onTriggered:{
                parent.color = idRandomColor.getRandomColor();
            }
        }
    }

}


