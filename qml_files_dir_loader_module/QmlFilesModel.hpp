#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd {

    class QmlFilesModel : public QAbstractListModel {
        Q_OBJECT
    private:
        Q_PROPERTY(QUrl qmlFilesDir READ getQmlFilesDir WRITE setQmlFilesDir NOTIFY qmlFilesDirChanged)
    public:
        enum AllRoles : int {
            FileNameRole = Qt::UserRole + 1,
            FilePathRole,
            SetParentWhenReleaseRole,
        };
    public:
        inline QUrl getQmlFilesDir() const;
        void setQmlFilesDir(const QUrl &);
        Q_SIGNAL void qmlFilesDirChanged();
    protected:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;
    private:
        void updateTheModel();
    private:
        QUrl thisQmlFilesDir;
        class Item {
        public:
            QString fileName;
            QFileInfo fileInfo;
            bool setParentWhenRelease{false};
        private:
            sstd_class(Item);
        };
        std::vector< Item, sstd::allocator<Item> > thisItems;
    private:
        sstd_class(QmlFilesModel);
    };

    inline QUrl QmlFilesModel::getQmlFilesDir() const {
        return thisQmlFilesDir;
    }

}/*namespace sstd*/



















