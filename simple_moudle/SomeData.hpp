#pragma once

#include "the_moudle.hpp"

namespace sstd {

    class SomeData : public QObject {
        Q_OBJECT
    public:
        Q_SLOT QColor getRandomColor() const;
    private:
        sstd_class(SomeData);
    };

}/*namespace sstd*/


