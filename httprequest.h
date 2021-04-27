#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkRequest>
#include <QtNetwork>
#include <QObject>
#include "notes_headers/noteslist.h"

class HttpRequest : public QObject
{
    Q_OBJECT
private:

    NotesList *notes;
    QString m_token;
    QUrl url;
public:

    Q_PROPERTY(NotesList *list READ list)
    Q_INVOKABLE void getHttpRequst();
    Q_INVOKABLE void autorization(QString login,QString password);
    Q_INVOKABLE void sendNote(int index);

    explicit HttpRequest(QObject *parent = nullptr);
    explicit HttpRequest(NotesList *list);

    NotesList *list() const;



    QString getToken() const;

private slots:
    void slotFinished(QNetworkReply*);
    void slotAutoriseFinished(QNetworkReply*);
    void sendNoteFinished(QNetworkReply*);

signals:
//    void authorisationFinished(QNetworkReply*,NotesItem*);
};

#endif // HTTPREQUEST_H
