
#include <sstd_qt_qml_quick_library.hpp>

int main(int argc, char ** argv) {

    sstd::QtApplication varApplication{ argc,argv };

    QQmlApplicationEngine varEngine;
    {
        /*获得Qml文件绝对路径*/
        auto varFullFileName = sstd::getLocalFileFullPath(
            QStringLiteral("appqml/hellow_world/main.qml"));
        /*加载Qml文件*/
        varEngine.load(varFullFileName);
        /*检查并报错*/
        if (varEngine.rootObjects().empty()) {
            return -1;
        }
    }
    return varApplication.exec();

}
