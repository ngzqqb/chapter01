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

        inline unsigned char typeOfService() const {
            return thisRep[1];
        }

        inline unsigned short totalLength() const {
            return decode(2, 3);
        }

        inline unsigned short identification() const {
            return decode(4, 5);
        }

        inline bool dontFragment() const {
            return (thisRep[6] & 0x40) != 0;
        }

        inline bool moreFragments() const {
            return (thisRep[6] & 0x20) != 0;
        }

        inline unsigned short fragmentOffset() const {
            return decode(6, 7) & 0x1FFF;
        }

        inline unsigned int timeToLive() const {
            return thisRep[8];
        }

        inline unsigned char protocol() const {
            return thisRep[9];
        }

        inline unsigned short headerChecksum() const {
            return decode(10, 11);
        }

        inline boost::asio::ip::address_v4 sourceAddress() const {
            boost::asio::ip::address_v4::bytes_type bytes = {
                { thisRep[12], thisRep[13], thisRep[14], thisRep[15] }
            };
            return boost::asio::ip::address_v4(bytes);
        }

        inline boost::asio::ip::address_v4 destinationAddress() const {
            boost::asio::ip::address_v4::bytes_type bytes = {
                { thisRep[16], thisRep[17], thisRep[18], thisRep[19] }
            };
            return boost::asio::ip::address_v4(bytes);
        }

        inline friend std::istream& operator>>(std::istream& argIs, IPV4Header& argHeader) {
            argIs.read(reinterpret_cast<char*>(argHeader.thisRep), 20);
            if (argHeader.version() != 4) {
                argIs.setstate(std::ios::failbit);
            }
            std::streamsize varOptionsLength = argHeader.headerLength() - 20;
            if (varOptionsLength < 0 || varOptionsLength > 40) {
                argIs.setstate(std::ios::failbit);
            } else {
                argIs.read(reinterpret_cast<char*>(argHeader.thisRep) + 20, varOptionsLength);
            }
            return argIs;
        }

    private:
        inline unsigned short decode(int a, int b) const {
            return (thisRep[a] << 8) + thisRep[b];
        }

        unsigned char thisRep[60];
    };

}/*namespace sstd*/
