# qml_files_dir_loader/qml_files_dir_loader.pro

TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = qml_files_dir_loader_debug
}else{
    TARGET = qml_files_dir_loader
}

SOURCES += $$PWD/main.cpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)
include($$PWD/../../sstd_library/add_vc_debug_console.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}

isEmpty(QMAKE_POST_LINK){
    QMAKE_POST_LINK += $${SSTD_LIBRARY_OUTPUT_PATH}/sstd_copy_qml $${PWD} $${PWD} skip
}else{
    QMAKE_POST_LINK += $$escape_expand(\\n\\t)$${SSTD_LIBRARY_OUTPUT_PATH}/sstd_copy_qml $${PWD} $${PWD} skip
}

CONFIG(debug,debug|release){
    DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"
}else{
    QMAKE_POST_LINK += $$escape_expand(\\n\\t)$${DESTDIR}/sstd_copy_qml $${PWD}/appqml $${DESTDIR}/appqml release
    export(QMAKE_POST_LINK)
}

QMLSOURCES += $$PWD/appqml/qml_files_dir_loader/main.qml

QMLSOURCES += $$PWD/appqml/qml_files_dir_loader/QmlFiles/One.qml
QMLSOURCES += $$PWD/appqml/qml_files_dir_loader/QmlFiles/Two.qml
QMLSOURCES += $$PWD/appqml/qml_files_dir_loader/QmlFiles/Three.qml
QMLSOURCES += $$PWD/appqml/qml_files_dir_loader/QmlFiles/PrivateBasic.qml

lupdate_only{
    SOURCES += $$QMLSOURCES
}

DISTFILES += $$QMLSOURCES
QML_IMPORT_PATH += $${SSTD_LIBRARY_OUTPUT_PATH}

#/*endl_input_of_latex_for_clanguage_lick*/"
