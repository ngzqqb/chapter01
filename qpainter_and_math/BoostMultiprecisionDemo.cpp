#include "BoostMultiprecisionDemo.hpp"

#include <limits>
#include <iomanip>
#include <sstream>
#include <iostream>

#include <sstd/boost/multiprecision/cpp_int.hpp>
#include <sstd/boost/multiprecision/cpp_dec_float.hpp>

namespace sstd {

    template<bool IsFloat = false, typename T>
    inline static QString toQString(const T & arg) {
        std::stringstream ss;
        if constexpr (IsFloat) {
            using U = std::remove_cv_t< std::remove_reference_t<T> >;
            ss << std::setprecision(std::numeric_limits<U>::digits10) << arg;
        } else {
            ss << arg;
        }
        std::string varTmp;
        ss >> varTmp;
        return QString::fromLatin1(varTmp.c_str(), static_cast<int>(varTmp.size()));
    }

    template<typename T>
    inline static auto formatText(T * arg) {
        arg->setTextWidth(230);
        arg->setFlag(QGraphicsItem::ItemIsMovable);
        return arg;
    }

    BoostMultiprecisionDemo::BoostMultiprecisionDemo()
        :SubWindowBasic(QStringLiteral("BoostMultiprecisionDemo")) {

        auto varScene = this->scene();

        using BInt = boost::multiprecision::cpp_int;
        using PBFloat = boost::multiprecision::cpp_dec_float<256>;
        using BFloat = boost::multiprecision::number<PBFloat>;

        qreal varHeight;
        {
            const BInt varA{ "+123456789123456789123456789" };
            const BInt varB{ "-789456123789456123789456123" };
            const BInt varC = varA * varB;
            varHeight = formatText(varScene->addText(toQString(varC)))
                ->boundingRect().height();
        }

        {
            BFloat varA{ "1.0000000000000000000000000000000000002" };
            for (auto varI = 0u; varI < 100u; ++varI) {
                varA *= varA;
            }
            formatText(varScene->addText(toQString<true>(varA)))
                ->setY(varHeight + 4.5);
        }

    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://www.boost.org/doc/libs/1_70_0/libs/multiprecision/doc/html/boost_multiprecision/tut/floats/fp_eg/aos.html

