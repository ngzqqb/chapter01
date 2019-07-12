#pragma once

#include "SubWindowBasic.hpp"

namespace sstd {

    class CGALDemo : public SubWindowBasic {
        Q_OBJECT
    public:
        CGALDemo();
        inline std::optional<QPointF> bestCenter() const override {
            return QPointF{ 100,68 };
        }
    private:
        sstd_class(CGALDemo);
    };

}/*namespace sstd*/



