
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = hellow_world_debug
}else{
    TARGET = hellow_world
}

SOURCES += $$PWD/main.cpp


include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}







