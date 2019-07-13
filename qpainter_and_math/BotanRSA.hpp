#pragma once

#include "SubWindowBasic.hpp"

namespace sstd {

    class BotanRSA final : public SubWindowBasic {
        Q_OBJECT
    public:
        BotanRSA();
    public:
        inline int bestWidth() const override {
            return 440;
        }
        inline int bestHeight() const override {
            return 440;
        }
    private:
        sstd_class(BotanRSA);
    };

}/*namespace sstd*/
