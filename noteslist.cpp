#include "noteslist.h"


NotesList::NotesList(QObject *parent) : QObject(parent)
{
    mNotes.append({"",0});
}



QVector<NotesItem> NotesList::items() const
{
    return mNotes;
}

bool NotesList::setItemAt(int index, const NotesItem &item)
{
    if(index<0 || index>mNotes.size())
        return false;
    mNotes[index]=item;
    return true;
}

void NotesList::appendItem()
{
    emit preItemAppended();

    NotesItem item;
    item.description="";
    item.id=1;
    mNotes.append(item);
    emit postItemAppended();
}
