
#include "Ping.hpp"
#include "PingObject.hpp"

namespace sstd {

    PingObject::PingObject(QObject * argParent) : QObject(argParent) {
    }

    class AsioiContext : public boost::asio::io_context {
    private:
        sstd_class(AsioiContext);
    };

    inline static unsigned short get_identifier() {

        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

#if defined(BOOST_ASIO_WINDOWS)
        return static_cast<unsigned short>(::GetCurrentProcessId());
#else
        return static_cast<unsigned short>(::getpid());
#endif
    }

    class GlobalPingObject {
        std::shared_ptr< boost::asio::io_context > thisContex;
        std::optional< boost::asio::executor_work_guard<boost::asio::io_context::executor_type> > thisQuit;
    public:
        inline auto & getContex() {
            if (!thisContex) {
                throw std::exception("the app has exit!");
            }
            return *thisContex;
        }

        inline GlobalPingObject() {
            thisContex = std::make_shared<AsioiContext>();
            thisQuit.emplace(boost::asio::make_work_guard(*thisContex));

            /*for ... */
            {
                std::thread([varContex = thisContex]() {
                    try {
                        varContex->run();
                    } catch (const std::exception & e) {
                        qWarning() << e.what();
                    }
                }).detach();
            }

            assert(qApp);
            QObject::connect(qApp, &QCoreApplication::aboutToQuit,
                qApp, [this]() {
                thisQuit->reset();
                thisQuit.reset();
                thisContex.reset();
            }, Qt::DirectConnection);

        }
        inline ~GlobalPingObject() {
        }
        inline static auto & instance() {
            static GlobalPingObject globalAns;
            return globalAns;
        }
    };

    bool startAPing(const QString & argSource) try {
       
        auto & varContex = GlobalPingObject::instance().getContex();
        const auto varSource = argSource.toUtf8();
        auto varPing = 
            std::make_shared<Ping>(varContex , varSource.constData());
        varPing->start();

        return true;
    } catch (const std::exception & e) {
        qDebug() << e.what();
        return false;
    }

    void PingObject::start(const QString & arg) {
        startAPing(arg);
    }

    PingObject::~PingObject() {
    }


}/*namespace sstd*/

inline static void regesterThis() {
    qmlRegisterType<sstd::PingObject>("sstd.ping", 1, 0, "Ping");
}
Q_COREAPP_STARTUP_FUNCTION(regesterThis)














