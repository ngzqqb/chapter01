/* two_point_line_module/the_moudle.cpp */

#include "the_moudle.hpp"
#include "Empty.hpp"

void sstd::TheMoudle::registerTypes(const char * argURI) {
    qmlRegisterType<Empty>(argURI, 1, 0, "Empty");
}

/*endl_input_of_latex_for_clanguage_lick*/
