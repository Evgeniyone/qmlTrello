#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkRequest>
#include <QtNetwork>
#include <QObject>
#include <QDateTime>
#include <TableList/tablelist.h>
#include "notes_headers/noteslist.h"

class HttpRequest : public QObject
{
    Q_OBJECT
private:

    TableList *tables;
    QString m_token;
    QUrl url;
    quint64 timestamp;
public:

    Q_PROPERTY(TableList *list READ list)
    Q_INVOKABLE void getHttpRequst();
    Q_INVOKABLE void autorization(QString login,QString password);
    Q_INVOKABLE void sendNote(int indexOfNote,int indexOfTable);
    //    Q_INVOKABLE void sinchronize();
    Q_INVOKABLE void deleteNote(int indexOfNote,int indexOfTable);

    explicit HttpRequest(QObject *parent = nullptr);
    explicit HttpRequest(TableList *list);

    TableList *list() const;

    QString getToken() const;

private slots:
    void slotFinished(QNetworkReply*);
    void slotAutoriseFinished(QNetworkReply*);
    void sendNoteFinished(QNetworkReply*,NotesItem*);
    //    void sinchronizeFinished(QNetworkReply*);
    void deleteNoteFinished(QNetworkReply*,int ,int);
};

#endif // HTTPREQUEST_H
