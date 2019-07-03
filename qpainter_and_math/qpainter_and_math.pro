
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

SOURCES += $$PWD/BoostGeometryDemo.cpp
HEADERS += $$PWD/BoostGeometryDemo.hpp

SOURCES += $$PWD/VoronoiPolygon.cpp
HEADERS += $$PWD/VoronoiPolygon.hpp

SOURCES += $$PWD/RTreeIndex.cpp
HEADERS += $$PWD/RTreeIndex.hpp

SOURCES += $$PWD/NearestPoint.cpp
HEADERS += $$PWD/NearestPoint.hpp

SOURCES += $$PWD/CGALDemo.cpp
HEADERS += $$PWD/CGALDemo.hpp

SOURCES += $$PWD/BoostGraphDemo.cpp
HEADERS += $$PWD/BoostGraphDemo.hpp

include($$PWD/../../sstd_library/sstd_library.pri)
include($$PWD/../../sstd_qt_qml_quick_library/sstd_qt_qml_quick_library.pri)
include($$PWD/../../sstd_library/add_vc_debug_console.pri)
include($$PWD/../../sstd_cgal/sstd_cgal.pri)

DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}
