
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = opengl_draw_debug
}else{
    TARGET = opengl_draw
}

SOURCES += $$PWD/main.cpp

SOURCES += $$PWD/Window.cpp
HEADERS += $$PWD/Window.hpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)
include($$PWD/../../sstd_library/add_vc_debug_console.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}
