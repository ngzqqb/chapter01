﻿#pragma once

#include "icmp_header.hpp"
#include "ipv4_header.hpp"
#include <sstd/boost/asio.hpp>
#include <sstd/boost/bind.hpp>
#include <string_view>
#include <sstd_library.hpp>

namespace sstd{

    class PingAns {
    public:
        std::atomic< std::int64_t > time{ 
            std::numeric_limits<std::int64_t>::max() 
        };
    private:
        sstd_class(PingAns);
    };

    class Ping : public std::enable_shared_from_this<Ping> {
    public:
        Ping(boost::asio::io_context& io_context, std::string_view destination);
    public:
        std::shared_ptr<PingAns> start();
    private:
        void start_send();
        void handle_timeout();
        void start_receive();
        void handle_receive(std::size_t length);
    private:
        static inline unsigned short get_identifier();
        using icmp = boost::asio::ip::icmp;
        icmp::resolver resolver_;
        icmp::endpoint destination_;
        icmp::socket socket_;
        boost::asio::steady_timer timer_;
        unsigned short sequence_number_;
        boost::asio::chrono::steady_clock::time_point time_sent_;
        boost::asio::streambuf reply_buffer_;
        std::size_t num_replies_;
        std::shared_ptr<PingAns> thisAns;
    private:
        sstd_class(Ping);
    };

}/*namespace sstd*/

