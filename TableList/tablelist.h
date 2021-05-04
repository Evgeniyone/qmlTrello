#ifndef TABLELIST_H
#define TABLELIST_H

#include <QObject>

#include "notes_headers/noteslist.h"

struct TableItem{
    int id;
    QString name;
    NotesList *list;
};

class TableList : public QObject
{
    Q_OBJECT

private:
    QVector <TableItem> *mTables;


public:
    explicit TableList(QObject *parent = nullptr);
    QVector<TableItem> *items();
    bool setItemAt(int index,TableItem &);
public slots:
    void appendItem();
signals:
    void preItemAppended();
    void postItemAppended();

};

#endif // TABLELIST_H
