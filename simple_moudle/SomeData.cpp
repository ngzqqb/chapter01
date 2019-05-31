#include "SomeData.hpp"

namespace sstd {

    QColor SomeData::getRandomColor() const{
        return QColor{
            ::rand()&255,::rand()&255,10,255
        };
    }

    QString SomeData::getString() const{
        return trUtf8(u8R"(你好世界！)");
    }

}/*namespace sstd*/
