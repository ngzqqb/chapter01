
import QtQuick 2.9
import QtQuick.Controls 2.5

ApplicationWindow {

    width: 360 ;
    height: 64 ;
    visible: true ;

    Label {
        text: qsTr("你好世界！");
        font.pointSize: 32;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        anchors.centerIn: parent;
    }

}
