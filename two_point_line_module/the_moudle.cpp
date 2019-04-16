/* two_point_line_module/the_moudle.cpp */

#include "the_moudle.hpp"
#include "Empty.hpp"
#include "TwoPoint.hpp"
#include "TwoPointLine.hpp"
#include "StaticCreator.hpp"

void sstd::TheMoudle::registerTypes(const char * argURI) {
    qmlRegisterType<Empty>(argURI, 1, 0, "Empty");
    qmlRegisterType<TwoPointLine>(argURI, 1, 0, "TwoPointLine");
    qmlRegisterSingletonType<Static>(argURI, 1, 0,
        "Static",
        &Static::instance);
}

/*endl_input_of_latex_for_clanguage_lick*/
