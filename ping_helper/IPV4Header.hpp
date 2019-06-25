#pragma once

#include <algorithm>
#include <iostream>
#include <sstd/boost/asio/ip/address_v4.hpp>

namespace sstd {

    class IPV4Header {
    public:
        inline IPV4Header() {
            std::fill(thisRep, thisRep + sizeof(thisRep), 0);
        }

        inline unsigned char version() const {
            return (thisRep[0] >> 4) & 0xF;
        }

        inline unsigned short headerLength() const {
            return (thisRep[0] & 0xF) * 4;
        }

        inline unsigned char type_of_service() const {
            return thisRep[1];
        }

        inline unsigned short total_length() const {
            return decode(2, 3);
        }

        inline unsigned short identification() const {
            return decode(4, 5);
        }

        inline bool dont_fragment() const {
            return (thisRep[6] & 0x40) != 0;
        }

        inline bool more_fragments() const {
            return (thisRep[6] & 0x20) != 0;
        }

        inline unsigned short fragment_offset() const {
            return decode(6, 7) & 0x1FFF;
        }

        inline unsigned int time_to_live() const {
            return thisRep[8];
        }

        inline unsigned char protocol() const {
            return thisRep[9];
        }

        inline unsigned short header_checksum() const {
            return decode(10, 11);
        }

        inline boost::asio::ip::address_v4 source_address() const {
            boost::asio::ip::address_v4::bytes_type bytes = {
                { thisRep[12], thisRep[13], thisRep[14], thisRep[15] }
            };
            return boost::asio::ip::address_v4(bytes);
        }

        inline boost::asio::ip::address_v4 destination_address() const {
            boost::asio::ip::address_v4::bytes_type bytes = {
                { thisRep[16], thisRep[17], thisRep[18], thisRep[19] }
            };
            return boost::asio::ip::address_v4(bytes);
        }

        inline friend std::istream& operator>>(std::istream& is, IPV4Header& header) {
            is.read(reinterpret_cast<char*>(header.thisRep), 20);
            if (header.version() != 4) {
                is.setstate(std::ios::failbit);
            }
            std::streamsize options_length = header.headerLength() - 20;
            if (options_length < 0 || options_length > 40) {
                is.setstate(std::ios::failbit);
            } else {
                is.read(reinterpret_cast<char*>(header.thisRep) + 20, options_length);
            }
            return is;
        }

    private:
        inline unsigned short decode(int a, int b) const {
            return (thisRep[a] << 8) + thisRep[b];
        }

        unsigned char thisRep[60];
    };

}/*namespace sstd*/
