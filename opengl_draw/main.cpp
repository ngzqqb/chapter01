
#include <sstd_qt_qml_quick_library.hpp>
#include "Window.hpp"

int main(int argc, char ** argv) {

    sstd::QtApplication varApplication{ argc,argv };

    sstd::Window window;
    window.resize(512, 256);
    window.show();

    return varApplication.exec();

}

