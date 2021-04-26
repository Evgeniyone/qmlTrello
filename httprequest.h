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
    QString m_token;
public:
    Q_PROPERTY(NotesList *list READ list)
    Q_INVOKABLE void getHttpRequst();

    explicit HttpRequest(QObject *parent = nullptr);
    explicit HttpRequest(NotesList *list);

    NotesList *list() const;


    Q_INVOKABLE void autorization(QString login,QString password);
    Q_INVOKABLE void sendNote(QString noteText);
    QString getToken() const;

private slots:
    void slotFinished(QNetworkReply*);
    void autoriseFinished(QNetworkReply*);
    void sendNoteFinished(QNetworkReply*);
signals:

};

#endif // HTTPREQUEST_H
