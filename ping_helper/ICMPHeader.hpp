#pragma once

#include <istream>
#include <ostream>
#include <algorithm>

namespace sstd {

    class ICMPHeader {
    public:
        enum {
            echo_reply = 0,
            destination_unreachable = 3,
            source_quench = 4,
            redirect = 5,
            echo_request = 8,
            time_exceeded = 11,
            parameter_problem = 12,
            timestamp_request = 13,
            timestamp_reply = 14,
            info_request = 15,
            info_reply = 16,
            address_request = 17,
            address_reply = 18
        };

        inline ICMPHeader() {
            std::fill(thisRep, thisRep + sizeof(thisRep), 0);
        }

        inline unsigned char type() const {
            return thisRep[0];
        }

        inline unsigned char code() const {
            return thisRep[1];
        }

        inline unsigned short checksum() const {
            return decode(2, 3);
        }

        inline unsigned short identifier() const {
            return decode(4, 5);
        }

        inline unsigned short sequence_number() const {
            return decode(6, 7);
        }

        inline void type(unsigned char n) {
            thisRep[0] = n;
        }

        inline void code(unsigned char n) {
            thisRep[1] = n;
        }

        inline void checksum(unsigned short n) {
            encode(2, 3, n);
        }

        inline void identifier(unsigned short n) {
            encode(4, 5, n);
        }

        inline void sequence_number(unsigned short n) {
            encode(6, 7, n);
        }

        inline friend std::istream& operator>>(std::istream& is, ICMPHeader& header) {
            return is.read(reinterpret_cast<char*>(header.thisRep), 8);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const ICMPHeader& header) {
            return os.write(reinterpret_cast<const char*>(header.thisRep), 8);
        }

    private:
        inline unsigned short decode(int a, int b) const {
            return (thisRep[a] << 8) + thisRep[b];
        }

        inline void encode(int a, int b, unsigned short n) {
            thisRep[a] = static_cast<unsigned char>(n >> 8);
            thisRep[b] = static_cast<unsigned char>(n & 0xFF);
        }

        unsigned char thisRep[8];
    };

    template <typename Iterator>
    inline void compute_checksum(ICMPHeader& header,
        Iterator body_begin, Iterator body_end) {
        unsigned int sum = (header.type() << 8) + header.code()
            + header.identifier() + header.sequence_number();

        Iterator body_iter = body_begin;
        while (body_iter != body_end) {
            sum += (static_cast<unsigned char>(*body_iter++) << 8);
            if (body_iter != body_end)
                sum += static_cast<unsigned char>(*body_iter++);
        }

        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        header.checksum(static_cast<unsigned short>(~sum));
    }

}/*namespace sstd*/


