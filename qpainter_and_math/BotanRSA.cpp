#include "BotanRSA.hpp"
#include <exception>
#include <sstd_botan.hpp>

namespace sstd {

    BotanRSA::BotanRSA() :
        SubWindowBasic(QStringLiteral("BotanRSA")) {

        std::string varPublicKey;
        std::string varPrivateKey;

        try { /*生成public key，private key*/
            Botan::AutoSeeded_RNG varRNG;
            Botan::RSA_PrivateKey varKey(varRNG, 1024);

            varPublicKey = Botan::X509::PEM_encode(varKey);
            varPrivateKey = Botan::PKCS8::PEM_encode(varKey);

            qDebug() << varPublicKey.c_str() << varPrivateKey.c_str();

        } catch (const std::exception & e) {
            qDebug() << e.what();
            return;
        }

        try {



        } catch (const std::exception & e) {
            qDebug() << e.what();
            return;
        }
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://github.com/ngzHappy/sstd_baidu_tieba_login
// https://botan.randombit.net/handbook/botan.pdf
// https://stackoverflow.com/questions/14263346/how-to-perform-asymmetric-encryption-with-botan
