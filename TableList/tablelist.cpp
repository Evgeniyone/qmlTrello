#include "tablelist.h"



TableList::TableList(QObject *parent) : QObject(parent)
{
    mTables = new QVector<TableItem>();
}

QVector<TableItem> *TableList::items()
{
    return mTables;
}

bool TableList::setItemAt(int index, TableItem &item)
{
    if(index<0 || index>mTables->size())
        return false;
    (*mTables)[index]=item;
    return true;
}

void TableList::appendItem()
{
    emit preItemAppended();
    TableItem item;
    item.name="ChangeName";
    item.id=1;
     /*app.getID();*/
    mTables->append(item);
    emit postItemAppended();
}



