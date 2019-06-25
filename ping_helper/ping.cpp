#include "Ping.hpp"
#include <string_view>
using namespace std::string_view_literals;

namespace sstd {

    using The = Ping;

    The::Ping(std::shared_ptr<PingAns> argPingAns,
        boost::asio::io_context& io_context) :
        socket_(io_context, icmp::v4()),
        sequence_number_(0) {
            {
                /*There may throw some exception ... */
                icmp::resolver resolver_{ io_context };
                destination_ = *resolver_.resolve(icmp::v4(), argPingAns->destination, ""sv).begin();
            }
            thisAns = std::move(argPingAns);
    }

    std::shared_ptr<PingAns> The::start() {
        auto varAns = thisAns;
        if (thisAns) {
            start_send();
        }
        if (thisAns) {
            start_receive();
        }
        return std::move(varAns);
    }

    void The::start_send() try {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        constexpr auto body = "\"Hello!\" from Asio ping."sv;

        /* Create an ICMP header for an echo request. */
        ICMPHeader echo_request;
        echo_request.type(ICMPHeader::echo_request);
        echo_request.code(0);
        echo_request.identifier(get_identifier());
        echo_request.sequence_number(++sequence_number_);
        compute_checksum(echo_request, body.begin(), body.end());

        /* Encode the request packet. */
        boost::asio::streambuf request_buffer;
        std::ostream os(&request_buffer);
        os << echo_request << body;

        /* Send the request. */
        time_sent_ = steady_timer::clock_type::now();
        socket_.send_to(request_buffer.data(), destination_);

    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        thisAns.reset();
    }

    void The::start_receive() try {
        /* Discard any data already in the buffer. */
        reply_buffer_.consume(reply_buffer_.size());

        /* Wait for a reply. We prepare the buffer to receive up to 64KB. */
        socket_.async_receive(reply_buffer_.prepare(65536),
            [varThis = this->shared_from_this()](const auto &, std::size_t argLength) {
            varThis->handle_receive(argLength);
        });

    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        thisAns.reset();
    }

    void The::handle_receive(std::size_t length)try {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        /* The actual number of bytes received is committed to the buffer so that we */
        /* can extract it using a std::istream object. */
        reply_buffer_.commit(length);

        if (!thisAns) {
            return;
        }

        /* Decode the reply packet. */
        std::istream is(&reply_buffer_);
        IPV4Header ipv4_hdr;
        ICMPHeader icmp_hdr;
        is >> ipv4_hdr >> icmp_hdr;

        /* We can receive all ICMP packets received by the host, so we need to */
        /* filter out only the echo replies that match the our identifier and */
        /* expected sequence number. */
        if (is && icmp_hdr.type() == ICMPHeader::echo_reply
            && icmp_hdr.identifier() == get_identifier()
            && icmp_hdr.sequence_number() == sequence_number_) {

            /* Print out some information about the reply packet. */
            auto elapsed = boost::asio::chrono::steady_clock::now() - time_sent_;
            thisAns->time = chrono::duration_cast<chrono::milliseconds>(elapsed).count();
            thisAns->IPV4Destination = ipv4_hdr.source_address().to_string();

#if defined(_DEBUG)
            std::cout << length - ipv4_hdr.headerLength()
                << " " << thisAns->destination
                << " bytes from "sv << thisAns->IPV4Destination
                << ": icmp_seq="sv << icmp_hdr.sequence_number()
                << ", ttl="sv << ipv4_hdr.time_to_live()
                << ", time="sv
                << thisAns->time
                << std::endl;
#endif 

        }

    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    Ping::~Ping() {
#if defined(_DEBUG)
        if (thisAns) {
            std::cout << "~Ping : " << thisAns->destination << std::endl;
        } else {
            std::cout << "~Ping" << std::endl;
        }
#endif
    }

    unsigned short The::get_identifier() {

        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

#if defined(BOOST_ASIO_WINDOWS)
        return static_cast<unsigned short>(::GetCurrentProcessId());
#else
        return static_cast<unsigned short>(::getpid());
#endif
    }

}/*namespace sstd*/



