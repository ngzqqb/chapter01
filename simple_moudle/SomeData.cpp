#include "SomeData.hpp"

namespace sstd {

    QColor SomeData::getRandomColor() const{
        return QColor{
            ::rand()&255,::rand()&255,10,255
        };
    }

}/*namespace sstd*/


