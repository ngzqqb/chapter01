#pragma once

#include "icmp_header.hpp"
#include "ipv4_header.hpp"
#include <sstd/boost/asio.hpp>
#include <sstd/boost/bind.hpp>

namespace sstd{

    class Ping {
    public:
        Ping(boost::asio::io_context& io_context, const char* destination);
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
    };

}/*namespace sstd*/

