#ifndef TABLELISTMODEL_H
#define TABLELISTMODEL_H

#include <QAbstractListModel>

#include "tablelist.h"

class TableListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        id=Qt::UserRole+1
        ,name
    };
    explicit TableListModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    TableList *mList;

    // QAbstractItemModel interface



    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

#endif // TABLELISTMODEL_H
