#pragma once

#include "the_moudle.hpp"

namespace sstd {

    class SomeData : public QObject {
        Q_OBJECT
    public:
        Q_SLOT QColor getRandomColor() const;
        Q_SLOT QString getString() const;
    private:
        sstd_class(SomeData);
    };

}/*namespace sstd*/
