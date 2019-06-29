#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class SubWindowBasic : public QGraphicsView {
        Q_OBJECT
    public:
        SubWindowBasic(const QString &);
    private:
        sstd_class(SubWindowBasic);
    };

}/*namespace sstd*/



