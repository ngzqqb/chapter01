﻿import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

/*begin:import*/
import theqml_the_debug.sstd.styled.app 1.0
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

        function setWindowTitle(window,titleName){
            if( window ) {
                if( winidow.title !== undefined ) {
                    winidow.title = titleName;
                }
            }
        }

        model: idTheModel
        delegate: Pane{
            width: idRootView.width
            height: 48
            leftPadding: 1
            rightPadding: 1
            topPadding: 1
            bottomPadding: 1
            leftInset: 0
            rightInset: 0
            bottomInset: 0
            topInset: 0

            RowLayout{
                Label{
                    text: fileName
                }
                Button{
                    text: qsTr("创建组件")
                    onClicked: {/*不缓存文件，直接创建...*/
                        /*begin:debug*/
                        if(true){
                            idRootView.setWindowTitle( Qt.createQmlObject(GlobalAppData.readLocalFile(filePath),
                                               GlobalAppData.privateDefaultWindow,
                                               filePath) , fileName );
                        }else
                            /*end:debug*/
                        {
                           var varComponent = Qt.createComponent( filePath );
                            if(varComponent.status === Component.Ready) try{
                                idRootView.setWindowTitle( varComponent.createObject(GlobalAppData.privateDefaultWindow)
                                                           , fileName );
                            }finally{
                                varComponent.destroy();
                            }
                        }
                    }
                }
            }/* RowLayout */
        }

    }/* ListView */

}/* ScrollView */

