#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>
#include <notes_headers/noteslist.h>

class NotesList;

class NotesModel : public QAbstractListModel
{
    Q_OBJECT



public:
    Q_PROPERTY(NotesList *list READ list WRITE setList)
    explicit NotesModel(QObject *parent = nullptr);
    enum Roles{
        id,description
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

    NotesList *list() const;
    void setList(NotesList *list);

//    Q_INVOKABLE void swapData(int _from, int _to); дописать
private:
    NotesList *mList;
};

#endif // NOTESMODEL_H
