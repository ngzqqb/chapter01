#include "MainWindow.hpp"
#include "QRegionDemo.hpp"
#include "BoostPolygonDemo.hpp"
#include "BoostGeometryDemo.hpp"
#include "VoronoiPolygon.hpp"
#include "RTreeIndex.hpp"
#include "CGALDemo.hpp"
#include "NearestPoint.hpp"
#include "BoostGraphDemo.hpp"
#include "BoostMultiprecisionDemo.hpp"
#include <array>

namespace sstd {

    template<typename T>
    inline static SubWindowBasic * theAddSubWindow(MainWindow * arg) {
        auto varWindow  = sstd_new< T >();
        auto varSubWindow = arg->addSubWindow(varWindow);
        varSubWindow->setWindowTitle(varWindow->objectName());
        varSubWindow->resize(varWindow->bestWidth(), varWindow->bestHeight());
        return varWindow;
    }

    MainWindow::MainWindow() {
        {/*初始化为最大桌面大小*/
            auto varDesktop = qApp->desktop();
            this->resize(varDesktop->availableGeometry(this).size());
        }
        std::array varSubWindows{
            theAddSubWindow<QRegionDemo>(this),
            theAddSubWindow<BoostPolygonDemo>(this),
            theAddSubWindow<BoostGeometryDemo>(this),
            theAddSubWindow<RTreeIndex>(this),
            theAddSubWindow<NearestPoint>(this),
            theAddSubWindow<VoronoiPolygon>(this),
            theAddSubWindow<CGALDemo>(this),
            theAddSubWindow<BoostGraphDemo>(this),
            theAddSubWindow<BoostMultiprecisionDemo>(this)
        };
#define THE_USE_PDF_PRINTER_VERSION (3u)
#if defined(THE_USE_PDF_PRINTER) && (THE_USE_PDF_PRINTER_VERSION!=2u)
        /*用于生成本书打印图片 ... */
        const QDir varOutDir{ THE_USE_PDF_PRINTER };
        const auto varPDF = QStringLiteral(".pdf");
        for (auto * varI : varSubWindows) {
            varI->printToPdf(
                varOutDir.absoluteFilePath(varI->objectName() + varPDF));
        }
#endif
    }

}/*namespace sstd*/
