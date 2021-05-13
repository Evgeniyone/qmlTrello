#include "tablelistmodel.h"

TableListModel::TableListModel(QObject *parent)
    : QAbstractListModel(parent),mList(nullptr)
{

}

void TableListModel::setListik(TableList *list)
{
    beginResetModel();
    if(mList)
        mList->disconnect(this);
    mList = list;

    connect(mList,&TableList::preItemAppended,this,[=](){
        const int index=mList->items()->size();
        beginInsertRows(QModelIndex(),index,index);
    });

    connect(mList,&TableList::postItemAppended,this,[=](){
        endInsertRows();
    });

    endResetModel();
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



    TableItem item=mList->items()->at(index.row());

    switch (role) {
    case Roles::id:
        return QVariant(item.id);
    case Roles::name:
        return QVariant(item.name);
    case Roles::list:
        return QVariant::fromValue(item.list);
    }

    return QVariant();
}


QHash<int, QByteArray> TableListModel::roleNames() const
{
    QHash<int,QByteArray> names;
    names[name]="name";
    names[id]="id";
    names[list]="list";
    return names;
}

TableList *TableListModel::listik() const
{
    return mList;
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
