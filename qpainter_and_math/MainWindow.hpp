#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class MainWindow : public QMdiArea {
        Q_OBJECT
    public:
        MainWindow();
    private:
        sstd_class(MainWindow);
    };

}/*namespace sstd*/
