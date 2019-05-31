#include "QmlFilesModel.hpp"

namespace sstd{

    void QmlFilesModel::setQmlFilesDir(const QString & arg){
        if( arg == thisQmlFilesDir ){
            return;
        }
        thisQmlFilesDir = arg;
        updateTheModel();
        qmlFilesDirChanged();
    }

    void QmlFilesModel::updateTheModel(){

        class LockItem{
            QmlFilesModel * const thisp;
        public:
            LockItem(QmlFilesModel * arg):thisp{arg}{
                thisp->beginResetModel();
            }
            ~LockItem(){
                thisp->endResetModel();
            }
        }varLock{this};

        /*清空数据*/
        thisItems.clear();

        {/*更新数据*/
            QDirIterator varIt{ thisQmlFilesDir ,QDir::Files | QDir::NoSymLinks |QDir::NoDotAndDotDot } ;
            while(varIt.hasNext()){
                auto varFileName = varIt.next();
                if(varFileName.isEmpty()){/*忽略空*/
                    continue;
                }
                if(!varFileName.endsWith(QStringLiteral(".qml"))){/*忽略非Qml*/
                    continue;
                }
                if(!varFileName[0].isUpper()){
                    continue;
                }
                if(varFileName.startsWith(QStringLiteral("Private"))){/*忽略Private*/
                    continue;
                }
                auto & varAns = thisItems.emplace_back();
                varAns.fileName = varFileName;
                varAns.fileInfo = varIt.fileInfo();
            }
        }

    }

    QHash<int,QByteArray> QmlFilesModel::roleNames() const{
        const static QHash<int,QByteArray> globalAns = [](){
            QHash<int,QByteArray> varAns;
            varAns[FileNameRole] =  QByteArrayLiteral("fileName");
            varAns[FilePathRole] =  QByteArrayLiteral("filePath");
            return std::move(varAns);
        }();
        return globalAns;
    }

    int QmlFilesModel::rowCount(const QModelIndex &  ) const {
        return static_cast<int>( thisItems.size() );
    }

    QVariant QmlFilesModel::data(const QModelIndex &index, int role  ) const {
        if(!index.isValid()){
            return {};
        }
        const auto varRowIndex = index.row();
        if(varRowIndex >= static_cast<int>( thisItems.size() ) ){
            return {};
        }
        if(varRowIndex<0){
            return {};
        }
        if( role == FileNameRole ){
            return thisItems[varRowIndex].fileName;
        }else if (role == FilePathRole) {
            return thisItems[varRowIndex].fileInfo.canonicalFilePath();
        }
    }

}/*namespace sstd*/

