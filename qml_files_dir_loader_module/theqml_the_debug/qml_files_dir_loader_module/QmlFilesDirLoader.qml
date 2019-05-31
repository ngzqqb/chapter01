import QtQuick 2.12
import QtQuick.Controls 2.12

/*begin:import*/
import theqml_the_debug.qml_files_dir_loader_module 1.0
/*end:import*/

ScrollView {

     property alias qmlFilesDir : idTheModel.qmlFilesDir

    ListView {

        id : idRootView
        QmlFilesModel{
            id : idTheModel
            /*filePath*/
            /*fileName*/
        }

        model: idTheModel
        delegate: Pane{
            width: idRootView.width
            height: 32
            leftPadding: 1
            rightPadding: 1
            topPadding: 1
            bottomPadding: 1
            leftInset: 0
            rightInset: 0
            bottomInset: 0
            topInset: 0
            Label{
                text: fileName
            }
        }

    }/* ListView */

}/* ScrollView */

