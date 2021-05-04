#ifndef NOTES_H
#define NOTES_H

#include <QObject>
#include <QVector>
enum Status{
    Sended,
    Deleted,
    Created

};
struct NotesItem{

    QString description;
    int id;
    bool sinchronize;
    int status;

};

class NotesList : public QObject
{
    Q_OBJECT
public:
    explicit NotesList(QObject *parent = nullptr);
    //explicit NotesList(NotesItem &item);
    QVector<NotesItem>* items();
    bool setItemAt(int index,NotesItem &);
    void changeItem(int index,NotesItem &after);

signals:
    void preItemAppended();
    void postItemAppended();
    void preItemDeleted(int index);
    void postItemDeleted();
    void dataChange(int index);


public slots:
    void appendItem();
    void appendItem(NotesItem item);
    void deleteItem(int index);
    void deleteItem(NotesItem*);




private:

    QVector <NotesItem> *mNotes;
};

#endif // NOTES_H
