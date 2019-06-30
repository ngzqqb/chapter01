#pragma once

#include "SubWindowBasic.hpp"

namespace sstd{

    class VoronoiPolygon : public SubWindowBasic {
        Q_OBJECT
    public:
        VoronoiPolygon();
    public:
        inline virtual int bestWidth() const override {
            return 512;
        }
    private:
        sstd_class(VoronoiPolygon);
    };

}/*namespace sstd*/

