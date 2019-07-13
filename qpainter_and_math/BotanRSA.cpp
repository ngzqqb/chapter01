#include "BotanRSA.hpp"
#include <exception>
#include <sstd_botan.hpp>

#include <string>
#include <string_view>

using namespace std::string_view_literals;
using namespace std::string_literals;

namespace sstd {

    template<typename T>
    inline static auto formatText(T * arg) {
        arg->setFlag(QGraphicsItem::ItemIsMovable);
        arg->setTextInteractionFlags(Qt::TextSelectableByMouse);
        return arg;
    }

    template<typename T>
    inline QString toQString(const T & arg) {
        return QString::fromUtf8(arg.data(), static_cast<int>(arg.size()));
    }

    BotanRSA::BotanRSA() :
        SubWindowBasic(QStringLiteral("BotanRSA")) {

        std::string varPublicKey;
        std::string varPrivateKey;
        const static auto varValue = u8R"(Hellow Botan!)"s;
        std::vector<uint8_t> varValueEncode;
        Botan::secure_vector<uint8_t> varValueDecode;
        const static auto varAlg = "EME-PKCS1-v1_5"s;

        try { /*生成public key，private key*/
            Botan::AutoSeeded_RNG varRNG;
            Botan::RSA_PrivateKey varKey(varRNG, 1024);

            varPublicKey = Botan::X509::PEM_encode(varKey);
            varPrivateKey = Botan::PKCS8::PEM_encode(varKey);

        } catch (const std::exception & e) {
            qWarning() << e.what();
            return;
        }

        try { /*使用public key进行加密*/
            Botan::DataSource_Memory varPublicKeyWrap{ varPublicKey };
            std::unique_ptr<Botan::Public_Key > varEncodeKey{
                Botan::X509::load_key(varPublicKeyWrap) };
            Botan::AutoSeeded_RNG varRNG;
            Botan::PK_Encryptor_EME varEncode{ *varEncodeKey ,varRNG ,varAlg };
            varValueEncode = varEncode.encrypt(reinterpret_cast<const uint8_t *>(varValue.c_str()),
                varValue.size(),
                varRNG);
        } catch (const std::exception & e) {
            qWarning() << e.what();
            return;
        }

        try { /*使用private key进行解密*/
            Botan::DataSource_Memory varPrivateKeyWrap{ varPrivateKey };
            Botan::AutoSeeded_RNG varRNG;
            std::unique_ptr<Botan::Private_Key > varDecodeKey{
                Botan::PKCS8::load_key(varPrivateKeyWrap, varRNG) };
            Botan::PK_Decryptor_EME varDecode{ *varDecodeKey,varRNG,varAlg };
            varValueDecode = varDecode.decrypt(varValueEncode.data(), varValueEncode.size());
        } catch (const std::exception & e) {
            qWarning() << e.what();
            return;
        }

        const std::string_view varAnsView{ 
            reinterpret_cast<const char *>(varValueDecode.data()) ,
            varValueDecode.size()};
        
        auto varScene = this->scene();
        auto varString = toQString(varValue);
        varString += QChar('\n');
        varString += QChar('\n');
        varString += toQString(varPublicKey);
        varString += QChar('\n');
        varString += toQString(varPrivateKey);
        varString += QChar('\n');
        varString += toQString(varAnsView);
        formatText(varScene->addText(varString));
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://github.com/ngzHappy/sstd_baidu_tieba_login
// https://botan.randombit.net/handbook/botan.pdf
// https://stackoverflow.com/questions/14263346/how-to-perform-asymmetric-encryption-with-botan
