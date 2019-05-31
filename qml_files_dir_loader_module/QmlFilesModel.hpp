#pragma once

#include <sstd_qt_qml_quick_library.hpp>

namespace sstd{

    class QmlFilesModel : public QAbstractListModel {
        Q_OBJECT
    private:
        Q_PROPERTY(QString qmlFilesDir READ getQmlFilesDir WRITE setQmlFilesDir NOTIFY qmlFilesDirChanged)
    public:
        inline QString getQmlFilesDir() const;
        void setQmlFilesDir(const QString &);
        Q_SIGNAL void qmlFilesDirChanged();
    protected:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    private:
        void updateTheModel();
    private:
        QString thisQmlFilesDir;
        class Item{
        public:
            QString fileName;
            QFileInfo fileInfo;
        private:
            sstd_class(Item);
        };
        std::vector< Item , sstd::allocator<Item> > thisItems;
    private:
        sstd_class(QmlFilesModel);
    };

    inline QString QmlFilesModel::getQmlFilesDir() const{
        return thisQmlFilesDir;
    }

}/*namespace sstd*/



















