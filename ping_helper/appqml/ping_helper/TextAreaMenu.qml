
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

MouseArea{

    id : idUrlMouseArea
    anchors.fill: parent   ;
    acceptedButtons: Qt.RightButton
    propagateComposedEvents : true
    property var textInput : parent ;
    property int selectionStart : 1;
    property int selectionEnd : 1;
    property bool isTextChanged: false;

    Connections{
        target: textInput;
        onTextChanged:{
            idUrlMenu.visible = false ;
        }
        enabled:idUrlMenu.visible
    }

    function reSelect(){
        if(idUrlMouseArea.isTextChanged){
            idUrlMouseArea.isTextChanged= false ;
            idUrlMouseArea.textInput.select( idUrlMouseArea.selectionStart,idUrlMouseArea.selectionEnd )
        }
    }

    onClicked: {
        selectionStart = textInput.selectionStart
        selectionEnd = textInput.selectionEnd
        isTextChanged  = true ;
        idUrlMenu.popup() ;
    }

    Menu{
        id : idUrlMenu

        MenuItem{
            text: qsTr("复制")
            onTriggered: {
                idUrlMouseArea.reSelect();
                idUrlMouseArea.textInput.copy()
            }
        }

    }
}
