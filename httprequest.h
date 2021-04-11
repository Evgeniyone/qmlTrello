#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkReply>
#include <QObject>
#include "notes_headers/noteslist.h"

class HttpRequest : public QObject
{
    Q_OBJECT
private:

   NotesList *notes;
public:
    explicit HttpRequest(QObject *parent = nullptr);
   explicit HttpRequest(NotesList *list);
    Q_PROPERTY(NotesList *list READ list)
    NotesList *list() const;
    Q_INVOKABLE void getHttpRequst();


private slots:
    void slotFinished(QNetworkReply*);
signals:

};

#endif // HTTPREQUEST_H
