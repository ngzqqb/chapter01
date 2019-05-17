
#include <sstd_qt_qml_quick_library.hpp>

int main(int argc, char ** argv) {

    sstd::QtApplication varApplication{ argc,argv };

    {
        auto varTranslator = sstd_virtual_new< QTranslator >();
        varTranslator->load( sstd::autoTheQMlPath<QString>(
                                  QStringLiteral("simple_moudle/the_en.qm")) );
        varApplication.installTranslator(varTranslator);
    }

    QQmlApplicationEngine varEngine;
    {
        /*获得Qml文件绝对路径*/
        auto varFullFileName = sstd::autoLocalPath<QUrl>(
            QStringLiteral("appqml/import_simple_moudle/main.qml"));
        /*加载Qml文件*/
        sstd::checkedLoadQmlFile(&varEngine, &varApplication, varFullFileName);
    }
    return varApplication.exec();

}
