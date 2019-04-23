#include <sstd_qt_qml_quick_library.hpp>

namespace sstd{

    class WindowOpenGLData;
    class Window : public QOpenGLWindow {
        Q_OBJECT
    private:
        using Super = QOpenGLWindow;
    protected:

        virtual void  initializeGL() override;
        virtual void  paintGL() override;
        virtual void resizeGL(int w, int h) override;
    private:
        std::weak_ptr< WindowOpenGLData > thisOpenGLData;
    };

}/*namespace sstd*/

