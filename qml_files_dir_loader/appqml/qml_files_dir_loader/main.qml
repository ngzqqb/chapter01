/* appqml/qml_files_dir_loader/main.qml */
import QtQuick 2.9
import QtQuick.Controls 2.5
import sstd.styled.app 1.0

/*begin:import*/
import theqml_the_debug.qml_files_dir_loader_module 1.0
/*end:import*/

StyledApplicationWindow {

    width: 360 ;
    height: 512 ;
    id : idRoot ; 
    Component.onCompleted: {
    }

    QmlFilesDirLoader{
        anchors.fill : parent
        qmlFilesDir  : Qt.resolvedUrl("QmlFiles")
    }

}
/*endl_input_of_latex_for_clanguage_lick*/
/*begin:debug*/
/*end:debug*/
