#include "MainWindow.hpp"
#include "QRegionDemo.hpp"
#include "BoostPolygonDemo.hpp"
#include "BoostGeometryDemo.hpp"
#include "VoronoiPolygon.hpp"
#include "RTreeIndex.hpp"
#include "CGALDemo.hpp"
#include "NearestPoint.hpp"
#include "BoostGraphDemo.hpp"

namespace sstd {

    template<typename T>
    inline static void theAddSubWindow(MainWindow * arg) {
        auto varWindow = sstd_new< T >();
        auto varSubWindow = arg->addSubWindow(varWindow);
        varSubWindow->setWindowTitle(varWindow->objectName());
        varSubWindow->resize(varWindow->bestWidth(), varWindow->bestHeight());
    }

    MainWindow::MainWindow() {
        {/*初始化为最大桌面大小*/
            auto varDesktop = qApp->desktop();
            this->resize(varDesktop->availableGeometry(this).size());
        }
        theAddSubWindow<QRegionDemo>(this);
        theAddSubWindow<BoostPolygonDemo>(this);
        theAddSubWindow<BoostGeometryDemo>(this);
        theAddSubWindow<RTreeIndex>(this);
        theAddSubWindow<NearestPoint>(this);
        theAddSubWindow<VoronoiPolygon>(this);
        theAddSubWindow<CGALDemo>(this);
        theAddSubWindow<BoostGraphDemo>(this);
    }

}/*namespace sstd*/
