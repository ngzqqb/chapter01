#include <sstd_qt_qml_quick_library.hpp>
#include "MainWindow.hpp"

int main(int argc, char ** argv) {

    sstd::QtApplication varApplication{ argc,argv };

    sstd::MainWindow varWindow;
    varWindow.show();

    return varApplication.exec();

}
