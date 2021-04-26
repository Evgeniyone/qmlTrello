#include "httprequest.h"

#include <QNetworkRequest>
#include <QtNetwork>
#include <QDebug>


HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{


}

HttpRequest::HttpRequest(NotesList *nlist):notes(nlist)
{

}

NotesList *HttpRequest::list() const
{
    return notes;
}

void HttpRequest::sendNote(QString noteText)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    QNetworkRequest request(QUrl("http://192.168.31.104:8080/cards"));

    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(sendNoteFinished(QNetworkReply*))
                );

    QJsonObject auref;
    auref["name"]=noteText;
    auref["numberOfList"]=1;
    auref["pos"]=1;

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    QJsonDocument doc(auref);
    QByteArray data = doc.toJson();
    accessManager->post(request,data);
}

void HttpRequest::autorization(QString login,QString password)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    QNetworkRequest request(QUrl("http://192.168.31.104:8080/login"));

    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(autoriseFinished(QNetworkReply*))
                );

    QJsonObject auref;
    auref["username"]=login;
    auref["password"]=password;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    QJsonDocument doc(auref);
    QByteArray data = doc.toJson();
    accessManager->post(request,data);
}



QString HttpRequest::getToken() const
{
    return m_token;
}

void HttpRequest::getHttpRequst()
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(slotFinished(QNetworkReply*))
                );
    QNetworkRequest request(QUrl("http://192.168.31.104:8080/cards"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    accessManager->get(request);

}

void HttpRequest::slotFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array=document.array();
    reply->rawHeader(QByteArray("Authorization"));

    for(auto note:array){
        NotesItem item;
        QJsonObject subtree = note.toObject();
        item.description=subtree.value("name").toString();
        item.id=subtree.value("id").toInt();
        notes->appendItem(item);
    }

}

void HttpRequest::autoriseFinished(QNetworkReply *reply)
{
    m_token=reply->rawHeader(QByteArray("Authorization"));
}

void HttpRequest::sendNoteFinished(QNetworkReply *)
{

}

