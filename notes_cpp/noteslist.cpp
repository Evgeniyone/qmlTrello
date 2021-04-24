#include "notes_headers/noteslist.h"


NotesList::NotesList(QObject *parent) : QObject(parent)
{
    mNotes.append({"",0,false});
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
    item.id=1;  /*app.getID();*/
    mNotes.append(item);
    emit postItemAppended();
}

void NotesList::appendItem(NotesItem item)
{
    emit preItemAppended();
    mNotes.append(item);
    emit postItemAppended();

}
