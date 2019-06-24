#pragma once

#include "icmp_header.hpp"
#include "ipv4_header.hpp"
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
        std::string destination;
        std::string IPV4Destination;
        inline void setToFinal() {
            finalTime = time.load();
        }
    private:
        sstd_class(PingAns);
    };

    class Ping : public std::enable_shared_from_this<Ping> {
    public:
        Ping(std::shared_ptr<PingAns> argPingAns, boost::asio::io_context& io_context );
        ~Ping();
    public:
        std::shared_ptr<PingAns> start();
    private:
        void start_send();
        void start_receive();
        void handle_receive(std::size_t length);
    private:
        static inline unsigned short get_identifier();
        using icmp = boost::asio::ip::icmp;
        icmp::endpoint destination_;
        icmp::socket socket_;
        unsigned short sequence_number_;
        boost::asio::chrono::steady_clock::time_point time_sent_;
        boost::asio::streambuf reply_buffer_;
        std::shared_ptr<PingAns> thisAns;
    private:
        sstd_class(Ping);
    };

}/*namespace sstd*/

