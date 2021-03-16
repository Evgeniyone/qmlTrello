#include "notesmodel.h"

NotesModel::NotesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int NotesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 2;
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch (role) {
    case Roles::id:
        return int(1);
    case Roles::description:
        return QVariant(QStringLiteral("Good\nGood\nGood\nGood\nGood"));
    }
    return QVariant();
}

bool NotesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
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
