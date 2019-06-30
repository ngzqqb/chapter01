#include "Ping.hpp"
#include <string_view>
using namespace std::string_view_literals;

namespace sstd {

    using The = Ping;

    The::Ping(std::shared_ptr<PingAns> argPingAns,
        boost::asio::io_context& argIOContext) :
        thisSocket(argIOContext, icmp::v4()),
        thisSequenceNumber(0) {
            {
                /*There may throw some exception ... */
                icmp::resolver resolver_{ argIOContext };
                thisDestination = *resolver_.resolve(icmp::v4(), argPingAns->destination, ""sv).begin();
            }
            thisAns = std::move(argPingAns);
    }

    std::shared_ptr<PingAns> The::start() {
        auto varAns = thisAns;
        if (thisAns) {
            startSend();
        }
        if (thisAns) {
            startReceive();
        }
        return std::move(varAns);
    }

    void The::startSend() try {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        constexpr auto varBody = "\"Hello!\" from Asio ping."sv;

        /* Create an ICMP header for an echo request. */
        ICMPHeader varEchoRequest;
        varEchoRequest.type(ICMPHeader::echo_request);
        varEchoRequest.code(0);
        varEchoRequest.identifier(get_identifier());
        varEchoRequest.sequenceNumber(++thisSequenceNumber);
        computeCheckSum(varEchoRequest, varBody.begin(), varBody.end());

        /* Encode the request packet. */
        boost::asio::basic_streambuf<sstd::allocator<char>> varRequestBuffer;
        std::ostream os(&varRequestBuffer);
        os << varEchoRequest << varBody;

        /* Send the request. */
        thisTimeSent = steady_timer::clock_type::now();
        thisSocket.send_to(varRequestBuffer.data(), thisDestination);

    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        thisAns.reset();
    }

    void The::startReceive() try {
        /* Discard any data already in the buffer. */
        thisReplyBuffer.consume(thisReplyBuffer.size());

        /* Wait for a reply. We prepare the buffer to receive up to 64KB. */
        thisSocket.async_receive(thisReplyBuffer.prepare(65536),
            [varThis = this->shared_from_this()](const auto &, std::size_t argLength) {
            varThis->handleReceive(argLength);
        });

    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        thisAns.reset();
    }

    void The::handleReceive(std::size_t length)try {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        /* The actual number of bytes received is committed to the buffer so that we */
        /* can extract it using a std::istream object. */
        thisReplyBuffer.commit(length);

        if (!thisAns) {
            return;
        }

        /* Decode the reply packet. */
        std::istream varIs(&thisReplyBuffer);
        IPV4Header varIPV4HDR;
        ICMPHeader varIMCPHDR;
        varIs >> varIPV4HDR >> varIMCPHDR;

        /* We can receive all ICMP packets received by the host, so we need to */
        /* filter out only the echo replies that match the our identifier and */
        /* expected sequence number. */
        if (varIs && varIMCPHDR.type() == ICMPHeader::echo_reply
            && varIMCPHDR.identifier() == get_identifier()
            && varIMCPHDR.sequenceNumber() == thisSequenceNumber) {

            /* Print out some information about the reply packet. */
            auto elapsed = boost::asio::chrono::steady_clock::now() - thisTimeSent;
            thisAns->time = chrono::duration_cast<chrono::milliseconds>(elapsed).count();
            thisAns->IPV4Destination = varIPV4HDR.sourceAddress().to_string();

#if defined(_DEBUG)
            std::cout << length - varIPV4HDR.headerLength()
                << " " << thisAns->destination
                << " bytes from "sv << thisAns->IPV4Destination
                << ": icmp_seq="sv << varIMCPHDR.sequenceNumber()
                << ", ttl="sv << varIPV4HDR.timeToLive()
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
