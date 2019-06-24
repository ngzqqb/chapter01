/* appqml/ping_helper/main.qml */
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

/*begin:import*/
import theqml_the_debug.sstd.styled.app 1.0
/*end:import*/

import sstd.ping 1.0

StyledApplicationWindow {

    width: 512 ;
    height: 360 ;
    id : idRoot ; 

    Ping{
        id : idPing
    }

    ColumnLayout{
        anchors.fill: parent
        RowLayout{
            Layout.fillWidth: true
            TextField{
                id : idUrl
                Layout.fillWidth: true
                text: "www.baidu.com"
            }
            Button{
                text: qsTr("启动")
                onClicked: {
                    idPing.start( idUrl.text )
                }
            }
        }
        TextArea{
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

}
/*endl_input_of_latex_for_clanguage_lick*/
/*begin:debug*/
/*end:debug*/
