/* qml_files_dir_loader/main.cpp */

#include <sstd_qt_qml_quick_library.hpp>

int main(int argc, char ** argv) {

    sstd::QtStyledApplication varApplication{ argc,argv };

    QQmlApplicationEngine varEngine;
    {
        /*获得Qml文件绝对路径*/
        auto varFullFileName = sstd::autoLocalPath<QUrl>(
            QStringLiteral("appqml/qml_files_dir_loader/main.qml"));
        /*加载Qml文件*/
        sstd::checkedLoadQmlFile(&varEngine, &varApplication, varFullFileName);
    }
    return varApplication.exec();

}

/*endl_input_of_latex_for_clanguage_lick*/
