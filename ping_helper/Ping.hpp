#pragma once

#include "ICMPHeader.hpp"
#include "IPV4Header.hpp"
#include <sstd/boost/asio.hpp>
#include <sstd/boost/bind.hpp>
#include <string_view>
#include <sstd_library.hpp>

namespace sstd {

    class PingAns {
    public:
        inline constexpr static std::int64_t invalidTime() {
            return std::numeric_limits<std::int64_t>::max();
        }
        inline bool isInvalid() const {
            return invalidTime() == finalTime;
        }
        std::atomic< std::int64_t > time{
            invalidTime()
        };
        std::int64_t finalTime{
            invalidTime()
        };
        const std::string destination;
        std::string IPV4Destination;
        inline void setToFinal() {
            finalTime = time.load();
        }
        inline PingAns(std::string_view arg) : destination{arg} {
        }
    private:
        sstd_class(PingAns);
    };

    class Ping : public std::enable_shared_from_this<Ping> {
    public:
        Ping(std::shared_ptr<PingAns> argPingAns, boost::asio::io_context& io_context);
        ~Ping();
    public:
        std::shared_ptr<PingAns> start();
    private:
        void startSend();
        void startReceive();
        void handleReceive(std::size_t length);
    private:
        static inline unsigned short get_identifier();
        using icmp = boost::asio::ip::icmp;
        icmp::endpoint thisDestination;
        icmp::socket thisSocket;
        unsigned short thisSequenceNumber;
        boost::asio::chrono::steady_clock::time_point thisTimeSent;
        boost::asio::streambuf thisReplyBuffer;
        std::shared_ptr<PingAns> thisAns;
    private:
        sstd_class(Ping);
    };

}/*namespace sstd*/

