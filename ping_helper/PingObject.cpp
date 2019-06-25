
#include "Ping.hpp"
#include "PingObject.hpp"

namespace sstd {

    PingObject::PingObject(QObject * argParent) : QObject(argParent) {
    }

    class AsioiContext : public boost::asio::io_context {
    private:
        sstd_class(AsioiContext);
    };

    class GlobalPingObject {
        std::shared_ptr< boost::asio::io_context > thisContex;
        std::optional< boost::asio::executor_work_guard<boost::asio::io_context::executor_type> > thisQuit;
    public:
        inline auto & getContex() {
            if (!thisContex) {
                throw std::runtime_error("the app has exit!");
            }
            return *thisContex;
        }

        inline GlobalPingObject() {
            thisContex = std::make_shared<AsioiContext>();
            thisQuit.emplace(boost::asio::make_work_guard(*thisContex));

            {
                auto varThreadCount = std::thread::hardware_concurrency();
                for (unsigned varI = 0; varI < varThreadCount; ++varI) {
                    std::thread([varContex = thisContex]() {
                        try {
                            varContex->run();
                        } catch (const std::exception & e) {
                            qWarning() << e.what();
                        }
                    }).detach();
                }
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

    inline static std::shared_ptr<PingAns> startAPing(const QString & argSource) {
        auto varAns = sstd_make_shared<PingAns>();
        {
            const auto varSource = argSource.toUtf8();
            varAns->destination = varSource.constData();
        }
        auto varPingStartFunction = [varAns]() {
            try {
                auto & varContex = GlobalPingObject::instance().getContex();
                auto varPing = std::make_shared<Ping>(varAns, varContex);
                varPing->start();
            } catch (const std::exception & e) {
                qDebug() << e.what();
            }
        };
        auto & varContex = GlobalPingObject::instance().getContex();
        varContex.post(std::move(varPingStartFunction));
        return std::move(varAns);
    }

    void PingObject::start(const QUrl & argLocalPingUrl, int argTimOut) {
        if (argTimOut < 1) {
            qWarning() << "check time : " << argTimOut << " is too small .";
            return;
        }
        if (thisIsPing) {
            qWarning() << "waiting for last ping finished !";
            return;
        }
        std::list< QString > varLines;
        {
            QFile varFile{ argLocalPingUrl.toLocalFile() };
            if (!varFile.open(QIODevice::ReadOnly)) {
                qWarning() << "can not open : " << argLocalPingUrl;
                return;
            }
            QTextStream varReadStream{ &varFile };
            while (!varReadStream.atEnd()) {
                auto varLine = varReadStream.readLine().trimmed();
                if (varLine.isEmpty()) {
                    continue;
                }
                varLines.emplace_back(varLine);
            }
        }
        varLines.sort();
        varLines.unique();
        if (varLines.empty()) {
            return;
        }
        thisPingAns.resize(varLines.size());
        {
            auto * varPointer = thisPingAns.data();
            for (const auto & varI : std::as_const(varLines)) {
                *varPointer = startAPing(varI);
                ++varPointer;
            }
        }
        setIsPing(true);
        QTimer::singleShot(argTimOut, this, [this]() {
            setIsPing(false);
        });
    }

    QString PingObject::pingAnsToString() {
        std::size_t varIsFinished = 0;
        for (auto & varI : thisPingAns) {
            varI->setToFinal();
            varIsFinished += !varI->isInvalid();
        }
        if (varIsFinished == thisPingAns.size()) {
            setIsPing(false);
        }
        std::sort(thisPingAns.begin(), thisPingAns.end(),
            [](const auto & argL, const auto & argR) {
            return argL->finalTime < argR->finalTime;
        });
        QString varAns;
        QTextStream varStream{ &varAns };
        for (const auto & varI : thisPingAns) {
            if (varI->isInvalid()) {
                varStream
                    << QString::fromUtf8(varI->destination.c_str())
                    << QStringLiteral(R"( time out)")
                    << '\n';
            } else {
                varStream
                    << QString::fromUtf8(varI->destination.c_str())
                    << '['
                    << QString::fromUtf8(varI->IPV4Destination.c_str())
                    << ']'
                    << QStringLiteral(" Time : ")
                    << varI->finalTime
                    << '\n';
            }
        }
        return std::move(varAns);
    }

    PingObject::~PingObject() {
    }

}/*namespace sstd*/

inline static void regesterThis() {
    qmlRegisterType<sstd::PingObject>("sstd.ping", 1, 0, "Ping");
}
Q_COREAPP_STARTUP_FUNCTION(regesterThis)














