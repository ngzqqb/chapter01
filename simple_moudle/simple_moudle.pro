TEMPLATE = lib
CONFIG += plugin

TARGET = $$qtLibraryTarget(simple_moudle)

SOURCES += $$PWD/the_moudle.cpp
HEADERS += $$PWD/the_moudle.hpp

SOURCES += $$PWD/SomeData.cpp
HEADERS += $$PWD/SomeData.hpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)

CONFIG(debug,debug|release){
    DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}/theqml_the_debug/simple_moudle
    QMAKE_POST_LINK += $${SSTD_LIBRARY_OUTPUT_PATH}/sstd_copy_qml $${PWD}/theqml_the_debug $${SSTD_LIBRARY_OUTPUT_PATH}/theqml_the_debug debug
}else{
    DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}/theqml/simple_moudle
    QMAKE_POST_LINK += $${SSTD_LIBRARY_OUTPUT_PATH}/sstd_copy_qml $${PWD}/theqml_the_debug $${SSTD_LIBRARY_OUTPUT_PATH}/theqml release
}
export(QMAKE_POST_LINK)



