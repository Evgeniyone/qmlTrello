#ifndef NOTES_H
#define NOTES_H

#include <QObject>
#include <QVector>

struct NotesItem{

    QString description;
    int id;
    bool sinchronize;
};

class NotesList : public QObject
{
    Q_OBJECT
public:
    explicit NotesList(QObject *parent = nullptr);
    //explicit NotesList(NotesItem &item);
    QVector<NotesItem> items() const;
    bool setItemAt(int index,const NotesItem &Item);

signals:
    void preItemAppended();
    void postItemAppended();
public slots:
    void appendItem();
    void appendItem(NotesItem item);


private:

    QVector <NotesItem> mNotes;
};

#endif // NOTES_H
