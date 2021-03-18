#include "notesmodel.h"

NotesModel::NotesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mList=new NotesList();

    connect(mList,&NotesList::preItemAppended,this,[=](){
        const int index=mList->items().size();
        beginInsertRows(QModelIndex(),index,index);
    });
    connect(mList,&NotesList::postItemAppended,this,[=](){
        endInsertRows();
    });



}

int NotesModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid()|| !mList)
        return 0;


    return mList->items().size();
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    NotesItem item=mList->items().at(index.row());

    switch (role) {
    case Roles::id:
        return QVariant(item.id);
    case Roles::description:
        return QVariant(item.description);
    }
    return QVariant();
}

bool NotesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
    {
        return false;
    }

    NotesItem item=mList->items().at(index.row());
    switch (role) {
    case Roles::id:
        item.id= value.toInt();
        break;

    case Roles::description:
        item.description=value.toString();
        break;
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;

}

Qt::ItemFlags NotesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> NotesModel::roleNames() const
{
    QHash<int,QByteArray> names;
    names[id]="id";
    names[description]="description";
    return names;

}

NotesList *NotesModel::list() const
{
    return mList;
}

void NotesModel::setList(NotesList *list)
{
    beginResetModel();
    if(list)
        mList->disconnect(this);
    mList = list;

    connect(mList,&NotesList::preItemAppended,this,[=](){
        const int index=mList->items().size();
        beginInsertRows(QModelIndex(),index,index);
    });
    connect(mList,&NotesList::postItemAppended,this,[=](){
        endInsertRows();
    });

    endResetModel();
}


