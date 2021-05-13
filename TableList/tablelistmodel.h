#ifndef TABLELISTMODEL_H
#define TABLELISTMODEL_H

#include <QAbstractListModel>

#include "tablelist.h"

class TableListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    Q_PROPERTY(TableList *list READ listik WRITE setListik)
    enum Roles{
        id=Qt::UserRole+1,
        name,
        list

    };

    explicit TableListModel(QObject *parent = nullptr);
    void setListik(TableList* list);
    QHash<int, QByteArray> roleNames() const override;
    TableList *listik()const;



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;




private:
    TableList *mList;

};

#endif // TABLELISTMODEL_H
