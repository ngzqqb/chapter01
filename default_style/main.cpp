﻿
#include <sstd_qt_qml_quick_library.hpp>

int main(int argc, char ** argv) {

    sstd::QtApplication varApplication{ argc,argv,{sstd::replaceFileName(argv[0],
        QStringLiteral("appqml/default_style/qtquickcontrols2.conf"))
    } };

    QQmlApplicationEngine varEngine;
    {
        /*获得Qml文件绝对路径*/
        auto varFullFileName = sstd::autoLocalPath<QUrl>(
            QStringLiteral("appqml/default_style/main.qml"));
        /*加载Qml文件*/
        sstd::checkedLoadQmlFile(&varEngine, &varApplication, varFullFileName);
    }
    return varApplication.exec();

}
