
#include "MainWindow.hpp"

namespace sstd {

    namespace the{

        class Scene final : public QGraphicsScene {
        public:
            inline Scene(QObject *parent):QGraphicsScene(parent){
            }
        private:
            sstd_class(Scene);
        };

    }/*namespace the*/

    MainWindow::MainWindow(){
        this->setScene(sstd_new<the::Scene>(this));
    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// 参考：
// https://github.com/ngzHappy/sstd_baidu_tieba_login

