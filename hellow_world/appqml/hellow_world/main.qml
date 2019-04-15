
import QtQuick 2.9
import QtQuick.Controls 2.5

ApplicationWindow {

    width: 360 ;
    height: 64 ;
    visible: true ;

    Text {
        text: qsTr("你好世界！");
        color: Qt.rgba(Math.random() / 10,
                       Math.random() / 10,
                       Math.random() / 10,
                       1.0);
        font.pointSize: 32;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        anchors.centerIn: parent;
    }

}

