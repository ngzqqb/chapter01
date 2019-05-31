/* qml_files_dir_loader_module/the_moudle.cpp */

#include "the_moudle.hpp"
#include "Empty.hpp"
#include "QmlFilesModel.hpp"

void sstd::TheMoudle::registerTypes(const char * argURI) {
    qmlRegisterType<Empty>(argURI, 1, 0, "Empty");
    qmlRegisterType<QmlFilesModel>(argURI, 1, 0, "QmlFilesModel");
}

/*endl_input_of_latex_for_clanguage_lick*/
