Using QML Modules with Plugins 

QML modules may use plugins to expose components defined in C++ to QML applications. Qt Creator cannot load the plugins to determine the details of the contained components, and therefore, the modules must provide extra type information for code completion and the semantic checks to work correctly.
To create a QML module and make it appear in the Library in the Design mode:
Create custom QML controls and place all the .qml files in a directory dedicated to your module.
Create a qmldir file for your module and place it in the module directory. For more information, see Module Definition qmldir Files.
Create a qmltypes file, preferably using qmlplugindump. For more information see, Generating qmltypes Files.
Create a directory named designer in your module directory.
Create a .metainfo file for your module and place it in the designer directory. Meta information is needed to display the components in the QML Types tab in the Library. Use a metainfo file delivered with Qt, such as qtquickcontrols2.metainfo, as an example.
Import your module into a project using QML_IMPORT_PATH in the .pro file: QML_IMPORT_PATH += path/to/module. For more information, see Importing QML Modules.
Make sure that the QML emulation layer used in the Design mode is built with the same Qt version as your QML modules. For more information, see Running QML Modules in Design Mode. You can also try skipping this step and take it later, if necessary.


qmlplugindump My.Module 1.0 /tmp/imports > /tmp/imports/My/Module/mymodule.qmltypes









