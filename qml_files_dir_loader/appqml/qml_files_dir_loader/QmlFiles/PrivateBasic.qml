
import QtQuick 2.12
import QtQuick.Controls 2.12

/*begin:import*/
import theqml_the_debug.sstd.styled.app 1.0
/*end:import*/

StyledWindow {
    id : idRoot
    width: 360
    height: 512
    visible: true

    /*begin:debug*/
    Component.onDestruction: {
        console.log("Destory Child Window")
    }
    /*end:debug*/

    onClosing: {
        idRoot.destroy();
    }

}
