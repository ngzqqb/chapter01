#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class Ping;
    class PingAns;
    class PingObject : public QObject {
        Q_OBJECT
    private:
        Q_PROPERTY(bool isPing READ getIsPing WRITE setIsPing NOTIFY isPingChanged)
    public:
        PingObject(QObject * argParent = nullptr);
        Q_INVOKABLE void start(const QUrl & argLocalPingUrl, int argTimOut = 5000);
        Q_INVOKABLE QString pingAnsToString();
        ~PingObject();
    public:
        inline bool getIsPing() const {
            return thisIsPing;
        }
        inline void setIsPing(const bool arg) {
            if (arg == thisIsPing) {
                return;
            }
            thisIsPing = arg;
            isPingChanged();
        }
        Q_SIGNAL void isPingChanged();
    private:
        QByteArray thisSource;
        bool thisIsPing{ false };
        std::vector< std::shared_ptr<PingAns> > thisPingAns;
    private:
        sstd_class(PingObject);
    };

}/*namespace sstd*/
