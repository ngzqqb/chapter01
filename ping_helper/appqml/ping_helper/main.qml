/* appqml/ping_helper/main.qml */
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

/*begin:import*/
import theqml_the_debug.sstd.styled.app 1.0
/*end:import*/

StyledApplicationWindow {

    width: 512 ;
    height: 360 ;
    id : idRoot ; 

    ColumnLayout{
        anchors.fill: parent
        RowLayout{
            Layout.fillWidth: true
            TextField{
                Layout.fillWidth: true
            }
            Button{
                text: qsTr("启动")
                onClicked: {
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
