
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

ApplicationWindow {

    width: 360 ;
    height: 64 ;
    visible: true ;
    id : idRoot

    function changeTheme(){
        if(idRoot.Material.theme === Material.Dark ){
            idRoot.Material.theme = Material.Light;
        }else{
            idRoot.Material.theme = Material.Dark;
        }
    }

    Label {
        text: qsTr("你好世界！");
        font.pointSize: 32;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        anchors.centerIn: parent;

        Timer{
            interval: 1236;
            running: true;
            repeat: true;
            onTriggered:changeTheme();
        }

    }

}
