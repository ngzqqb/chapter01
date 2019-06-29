
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = qpainter_and_math_debug
}else{
    TARGET = qpainter_and_math
}

SOURCES += $$PWD/main.cpp

SOURCES += $$PWD/MainWindow.cpp
HEADERS += $$PWD/MainWindow.hpp

SOURCES += $$PWD/SubWindowBasic.cpp
HEADERS += $$PWD/SubWindowBasic.hpp

SOURCES += $$PWD/QRegionDemo.cpp
HEADERS += $$PWD/QRegionDemo.hpp

SOURCES += $$PWD/BoostPolygonDemo.cpp
HEADERS += $$PWD/BoostPolygonDemo.hpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)
include($$PWD/../../sstd_library/add_vc_debug_console.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}



