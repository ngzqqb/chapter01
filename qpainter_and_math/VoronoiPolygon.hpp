﻿#pragma once

#include "SubWindowBasic.hpp"

namespace sstd {

    class VoronoiPolygon final : public SubWindowBasic {
        Q_OBJECT
    public:
        VoronoiPolygon();
    public:
        inline virtual int bestWidth() const override {
            return 512;
        }
        inline std::optional<QPointF> bestCenter() const override {
            return QPointF{ 100,0 };
        }
    private:
        sstd_class(VoronoiPolygon);
    };

}/*namespace sstd*/

