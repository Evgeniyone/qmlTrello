#include "notes_headers/noteslist.h"


NotesList::NotesList(QObject *parent) : QObject(parent)
{
    mNotes=new QVector<NotesItem> ();
//    mNotes.append({"",0,false});
}



QVector<NotesItem>* NotesList::items()
{
    return mNotes;
}

bool NotesList::setItemAt(int index,  NotesItem &item)
{
    if(index<0 || index>mNotes->size())
        return false;
    (*mNotes)[index]=item;
    return true;
}

void NotesList::appendItem()
{
    emit preItemAppended();

    NotesItem item;
    item.description="";
    item.id=1;
    item.status=Status::Created;    /*app.getID();*/
    mNotes->append(item);
    emit postItemAppended();
}

void NotesList::appendItem(NotesItem item)
{
    emit preItemAppended();
    mNotes->append(item);
    emit postItemAppended();

}

void NotesList::deleteItem(NotesItem *item)
{
    int index=std::distance(mNotes->begin(),item);
    emit preItemDeleted(index);

    mNotes->erase(item);
    emit postItemDeleted();


}

void NotesList::changeItem(int index,NotesItem &after)
{
    (*mNotes)[index].description=after.description;
    emit dataChange(index);

}
