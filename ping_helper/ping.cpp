#include "Ping.hpp"

namespace sstd {

    using The = Ping ;

    The::Ping(boost::asio::io_context& io_context, const char* destination):
        resolver_(io_context),
        socket_(io_context,
        icmp::v4()),
        timer_(io_context),
        sequence_number_(0),
        num_replies_(0){
        destination_ = *resolver_.resolve(icmp::v4(), destination, "").begin();
        start_send();
        start_receive();
    }

    void The::start_send() {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        const static std::string_view body = "\"Hello!\" from Asio ping."sv ;

        /* Create an ICMP header for an echo request. */
        icmp_header echo_request;
        echo_request.type(icmp_header::echo_request);
        echo_request.code(0);
        echo_request.identifier(get_identifier());
        echo_request.sequence_number(++sequence_number_);
        compute_checksum(echo_request, body.begin(), body.end());

        /* Encode the request packet. */
        boost::asio::streambuf request_buffer;
        if constexpr(false ) {
            std::ostream os(&request_buffer);
            os << echo_request << body;
        }

        /* Send the request. */
        time_sent_ = steady_timer::clock_type::now();
        socket_.send_to(request_buffer.data(), destination_);

        /* Wait up to five seconds for a reply. */
        num_replies_ = 0;
        timer_.expires_at(time_sent_ + chrono::seconds(5));
        timer_.async_wait(boost::bind(&The::handle_timeout, this));
      }

    void The::handle_timeout() {

        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

        if (num_replies_ == 0){
          std::cout << "Request timed out" << std::endl;
            }

        /* Requests must be sent no less than one second apart. */
        timer_.expires_at(time_sent_ + chrono::seconds(1));
        timer_.async_wait(boost::bind(&The::start_send, this));
      }

    void The::start_receive()  {
        /* Discard any data already in the buffer. */
        reply_buffer_.consume(reply_buffer_.size());

        /* Wait for a reply. We prepare the buffer to receive up to 64KB. */
        socket_.async_receive(reply_buffer_.prepare(65536),
            boost::bind(&The::handle_receive, this, _2));
      }

    void The::handle_receive(std::size_t length) {
        using boost::asio::steady_timer;
        namespace chrono = boost::asio::chrono;

       /* The actual number of bytes received is committed to the buffer so that we */
       /* can extract it using a std::istream object. */
       reply_buffer_.commit(length);

       /* Decode the reply packet. */
       std::istream is(&reply_buffer_);
       ipv4_header ipv4_hdr;
       icmp_header icmp_hdr;
       is >> ipv4_hdr >> icmp_hdr;

       /* We can receive all ICMP packets received by the host, so we need to */
       /* filter out only the echo replies that match the our identifier and */
       /* expected sequence number. */
       if (is && icmp_hdr.type() == icmp_header::echo_reply
             && icmp_hdr.identifier() == get_identifier()
             && icmp_hdr.sequence_number() == sequence_number_)  {

         /* If this is the first reply, interrupt the five second timeout. */
         if (num_replies_++ == 0){
           timer_.cancel();
         }

         /* Print out some information about the reply packet. */
         auto elapsed = boost::asio::chrono::steady_clock::now() - time_sent_ ;
         std::cout << length - ipv4_hdr.header_length()
           << " bytes from " << ipv4_hdr.source_address()
           << ": icmp_seq=" << icmp_hdr.sequence_number()
           << ", ttl=" << ipv4_hdr.time_to_live()
           << ", time="
           << chrono::duration_cast<chrono::milliseconds>(elapsed).count()
           << std::endl;
       }

       start_receive();
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



