#pragma once

#include <sstd_qt_qml_quick_library.hpp>
#include "icmp_header.hpp"
#include "ipv4_header.hpp"

namespace sstd{

    class Ping  : public QObject {
        Q_OBJECT
    private:
        sstd_class (Ping);
    };

}/*namespace sstd*/



