#include "BoostMultiprecisionDemo.hpp"

#include <limits>
#include <iomanip>
#include <iostream>

#include <sstd/boost/multiprecision/cpp_int.hpp>
#include <sstd/boost/multiprecision/cpp_dec_float.hpp>

namespace sstd {

    BoostMultiprecisionDemo::BoostMultiprecisionDemo()
        :SubWindowBasic(QStringLiteral("BoostMultiprecisionDemo")) {

        using BInt = boost::multiprecision::cpp_int;
        using BFloat = boost::multiprecision::cpp_dec_float<256>;

        {
            BInt varA{ "123456789123456789123456789" };
            BInt varB{ "789456123789456123789456123" };
            BInt varC = varA * varB;
            std::cout << varC << std::endl;
        }

        {
            BFloat varA{ "1.0000000000000000000000000000000000002" };
            for (auto varI = 0u; varI < 100u; ++varI) {
                varA *= varA;
            }
            std::cout
                << std::setprecision(std::numeric_limits<BFloat>::digits10)
                //<< varA
                << std::endl;
        }

    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://www.boost.org/doc/libs/1_70_0/libs/multiprecision/doc/html/boost_multiprecision/tut/floats/fp_eg/aos.html

