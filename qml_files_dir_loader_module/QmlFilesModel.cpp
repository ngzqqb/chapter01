#include "QmlFilesModel.hpp"

namespace sstd {

    void QmlFilesModel::setQmlFilesDir(const QUrl & arg) {
        if (arg == thisQmlFilesDir) {
            return;
        }
        thisQmlFilesDir = arg;
        updateTheModel();
        qmlFilesDirChanged();
    }

    void QmlFilesModel::updateTheModel() {

        QString varLocalFileDir = thisQmlFilesDir.toLocalFile();

        class LockItem {
            QmlFilesModel * const thisp;
        public:
            LockItem(QmlFilesModel * arg) :thisp{ arg } {
                thisp->beginResetModel();
            }
            ~LockItem() {
                thisp->endResetModel();
            }
        }varLock{ this };

        /*清空数据*/
        thisItems.clear();

        {/*更新数据*/
            QDirIterator varIt{ varLocalFileDir ,QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot };
            while (varIt.hasNext()) {
                auto varFileName = varIt.next();
                auto varFileInfo = varIt.fileInfo();
                varFileName = varFileInfo.fileName();
                if (varFileName.isEmpty()) {/*忽略空*/
                    continue;
                }
                if (!varFileName.endsWith(QStringLiteral(".qml"))) {/*忽略非Qml*/
                    continue;
                }
                if (!varFileName[0].isUpper()) {
                    continue;
                }
                if (varFileName.startsWith(QStringLiteral("Private"))) {/*忽略Private*/
                    continue;
                }
                auto & varAns = thisItems.emplace_back();
                varAns.fileName = std::move(varFileName);
                varAns.fileInfo = std::move(varFileInfo);
                {
                    QFile varFile{ varAns.fileInfo.canonicalFilePath() };
                    if (varFile.open(QIODevice::ReadOnly)) {
                        QTextStream varRead{ &varFile };
                        varRead.setCodec( QTextCodec::codecForName("UTF-8") );
                        const auto varAllLines = varRead.readAll();
                        varAns.setParentWhenRelease = varAllLines.indexOf( 
                            QStringLiteral("//@setParentWhenRelease(true)") ) >= 0;
                    }
                }
            }
        }

        {/*排序名称*/
            std::sort(thisItems.begin(), thisItems.end(), [](const auto & l, const auto & r) ->bool {
                const auto & ln = l.fileName;
                const auto & rn = r.fileName;
                if (ln.size() < rn.size()) {
                    return true;
                } else if (ln.size() > rn.size()) {
                    return false;
                }
                return ln < rn;
            });
        }

    }

    QHash<int, QByteArray> QmlFilesModel::roleNames() const {
        const static QHash<int, QByteArray> globalAns = []() {
            QHash<int, QByteArray> varAns;
            varAns[FileNameRole] = QByteArrayLiteral("fileName");
            varAns[FilePathRole] = QByteArrayLiteral("filePath");
            varAns[SetParentWhenReleaseRole] = QByteArrayLiteral("setParentWhenRelease");
            return std::move(varAns);
        }();
        return globalAns;
    }

    int QmlFilesModel::rowCount(const QModelIndex &) const {
        return static_cast<int>(thisItems.size());
    }

    QVariant QmlFilesModel::data(const QModelIndex &index, int role) const {
        if (!index.isValid()) {
            return {};
        }
        const auto varRowIndex = index.row();
        if (varRowIndex >= static_cast<int>(thisItems.size())) {
            return {};
        }
        if (varRowIndex < 0) {
            return {};
        }
        if (role == FileNameRole) {
            return thisItems[varRowIndex].fileName;
        } else if (role == FilePathRole) {
            return QUrl::fromLocalFile(thisItems[varRowIndex].fileInfo.canonicalFilePath());
        } else if (role == SetParentWhenReleaseRole) {
            return thisItems[varRowIndex].setParentWhenRelease;
        }
        return{};
    }

}/*namespace sstd*/

