#include "LoginFunction.hpp"

namespace sstd{

    class LoginFunction final :
            public QObject ,
            public sstd::YieldResumeFunction {
        Q_OBJECT
    public:
        LoginFunction();
    private:
        sstd_class(LoginFunction);
    };

}/*namespace sstd*/

