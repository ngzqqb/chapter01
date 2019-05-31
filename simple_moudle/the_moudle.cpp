#include "the_moudle.hpp"
#include "SomeData.hpp"

void sstd::TheMoudle::registerTypes(const char *uri){
    qmlRegisterType<SomeData>(uri, 1, 0, "SomeData");
}
