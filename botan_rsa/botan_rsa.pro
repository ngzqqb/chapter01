
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = botan_rsa_debug
}else{
    TARGET = botan_rsa
}

SOURCES += $$PWD/main.cpp

SOURCES += $$PWD/MainWindow.cpp
HEADERS += $$PWD/MainWindow.hpp

SOURCES += $$PWD/LoginFunction.cpp
HEADERS += $$PWD/LoginFunction.hpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)
include($$PWD/../../sstd_library/add_vc_debug_console.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}










