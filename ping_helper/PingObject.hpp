#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd{

    class Ping;
    class PingObject : public QObject {
        Q_OBJECT
    public:
        PingObject(QObject * argParent = nullptr);
        Q_INVOKABLE void start( const QString & );
        ~PingObject();
    private:
        Ping * thisPing{nullptr};
        QByteArray thisSource;
    private:
        sstd_class ( PingObject );
    };

}/*namespace sstd*/






