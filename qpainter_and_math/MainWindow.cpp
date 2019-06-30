#include "MainWindow.hpp"
#include "QRegionDemo.hpp"
#include "BoostPolygonDemo.hpp"
#include "BoostGeometryDemo.hpp"
#include "TrianglePolygon.hpp"

namespace sstd {

    template<typename T>
    inline static void theAddSubWindow(MainWindow * arg) {
        auto varWindow = sstd_new< T >();
        auto varSubWindow = arg->addSubWindow(varWindow);
        varSubWindow->resize(512, 512);
        varSubWindow->setWindowTitle(varWindow->objectName());
    }

    MainWindow::MainWindow() {
        this->resize(1024, 768);
        theAddSubWindow<QRegionDemo>(this);
        theAddSubWindow<BoostPolygonDemo>(this);
        theAddSubWindow<BoostGeometryDemo>(this);
        theAddSubWindow<TrianglePolygon>(this);
    }

}/*namespace sstd*/
