
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = import_simple_moudle_debug
}else{
    TARGET = import_simple_moudle
}

SOURCES += $$PWD/main.cpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}

CONFIG(debug,debug|release){
    DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"
}else{
    QMAKE_POST_LINK += $${DESTDIR}/sstd_copy_qml $${PWD}/appqml $${DESTDIR}/appqml release
    export(QMAKE_POST_LINK)
}

QMLSOURCES += $$PWD/appqml/import_simple_moudle/main.qml

lupdate_only{
    SOURCES += $$QMLSOURCES
}

DISTFILES += $$QMLSOURCES
QML_IMPORT_PATH += $${SSTD_LIBRARY_OUTPUT_PATH}

