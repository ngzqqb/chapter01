
TEMPLATE = app

CONFIG(debug,debug|release){
    TARGET = hellow_world_debug
}else{
    TARGET = hellow_world
}

SOURCES += $$PWD/main.cpp










