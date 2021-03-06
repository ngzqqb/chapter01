﻿#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class SubWindowBasic : public QGraphicsView {
        Q_OBJECT
    public:
        SubWindowBasic(const QString &);
    public:
        inline virtual int bestWidth() const {
            return 1024 / 3;
        }
        inline virtual int bestHeight() const {
            return 768 / 2;
        }
        inline virtual std::optional<QPointF> bestCenter() const {
            return {};
        }
    public:
        virtual void printToPdf(const QString &) const ;
    private:
        sstd_class(SubWindowBasic);
    };

}/*namespace sstd*/
