#pragma once

#include <algorithm>
#include <iostream>
#include <sstd/boost/asio/ip/address_v4.hpp>

class ipv4_header {
public:
    inline ipv4_header() {
        std::fill(rep_, rep_ + sizeof(rep_), 0);
    }

    inline unsigned char version() const {
        return (rep_[0] >> 4) & 0xF;
    }

    inline unsigned short header_length() const {
        return (rep_[0] & 0xF) * 4;
    }

    inline unsigned char type_of_service() const {
        return rep_[1];
    }

    inline unsigned short total_length() const {
        return decode(2, 3);
    }

    inline unsigned short identification() const {
        return decode(4, 5);
    }

    inline bool dont_fragment() const {
        return (rep_[6] & 0x40) != 0;
    }

    inline bool more_fragments() const {
        return (rep_[6] & 0x20) != 0;
    }

    inline unsigned short fragment_offset() const {
        return decode(6, 7) & 0x1FFF;
    }

    inline unsigned int time_to_live() const {
        return rep_[8];
    }

    inline unsigned char protocol() const {
        return rep_[9];
    }

    inline unsigned short header_checksum() const {
        return decode(10, 11);
    }

    inline boost::asio::ip::address_v4 source_address() const {
        boost::asio::ip::address_v4::bytes_type bytes = {
            { rep_[12], rep_[13], rep_[14], rep_[15] }
        };
        return boost::asio::ip::address_v4(bytes);
    }

    inline boost::asio::ip::address_v4 destination_address() const {
        boost::asio::ip::address_v4::bytes_type bytes = {
            { rep_[16], rep_[17], rep_[18], rep_[19] }
        };
        return boost::asio::ip::address_v4(bytes);
    }

    inline friend std::istream& operator>>(std::istream& is, ipv4_header& header) {
        is.read(reinterpret_cast<char*>(header.rep_), 20);
        if (header.version() != 4) {
            is.setstate(std::ios::failbit);
        }
        std::streamsize options_length = header.header_length() - 20;
        if (options_length < 0 || options_length > 40) {
            is.setstate(std::ios::failbit);
        } else {
            is.read(reinterpret_cast<char*>(header.rep_) + 20, options_length);
        }
        return is;
    }

private:
    inline unsigned short decode(int a, int b) const {
        return (rep_[a] << 8) + rep_[b];
    }

    unsigned char rep_[60];
};

