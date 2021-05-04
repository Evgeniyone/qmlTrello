#include "tablelistmodel.h"

TableListModel::TableListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mList = new TableList ();
}



int TableListModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid() && !mList)
        return 0;

    return mList->items()->size();

}

QVariant TableListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
    if (!index.isValid())
        return QVariant();

    TableItem item=mList->items()->at(index.row());

    switch (role) {
    case Roles::id:
        return QVariant(item.id);
    case Roles::name:
        return QVariant(item.name);
    }
    return QVariant();
}


QHash<int, QByteArray> TableListModel::roleNames() const
{
    QHash<int,QByteArray> names;
    names[name]="name";
    names[id]="id";
    return names;
}


bool TableListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
    {
        return false;
    }

    TableItem item=mList->items()->at(index.row());
    switch (role) {
    case Roles::id:
        item.id= value.toInt();
        break;

    case Roles::name:
        item.name=value.toString();
        break;
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;

}
