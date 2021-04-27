#include "httprequest.h"

#include <QNetworkRequest>
#include <QtNetwork>
#include <QDebug>
#include <algorithm>


HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{

    
}

HttpRequest::HttpRequest(NotesList *nlist):notes(nlist)
{
    url="http://192.168.31.104:8080/";
}

NotesList *HttpRequest::list() const
{
    return notes;
}

void HttpRequest::sendNote(int index)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    QNetworkRequest request(QUrl(url.toString()+"cards"));
    
    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(sendNoteFinished(QNetworkReply*))
                );
    
    QJsonObject auref;
    NotesItem *item=&(*notes->items())[index];

    auref["name"]=item->description;
    auref["numberOfList"]=1;
    auref["pos"]=1;
    
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    QJsonDocument doc(auref);
    QByteArray data = doc.toJson();
    if(item->status==Status::Created)
    {
        accessManager->post(request,data);

        item->status=Status::Sended;

    }
    else
    {

        QString m=url.toString()+"cards/"+QString::number(item->id);
        qDebug()<<m;
        QNetworkRequest request(QUrl(m.toUtf8()));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
        QJsonObject auref;
        auref["name"]=item->description;
        QJsonDocument doc(auref);
        QByteArray data = doc.toJson();
        accessManager->put(request,data);
    }
}

void HttpRequest::sendNoteFinished(QNetworkReply *reply)
{
    QByteArray data= reply->readAll();

}



void HttpRequest::autorization(QString login,QString password)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    QNetworkRequest request(QUrl(url.toString()+"login"));


    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(slotAutoriseFinished(QNetworkReply*))
                );

    QJsonObject auref;
    auref["username"]=login;
    auref["password"]=password;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    QJsonDocument doc(auref);
    QByteArray data = doc.toJson();
    accessManager->post(request,data);

}

void HttpRequest::slotAutoriseFinished(QNetworkReply *reply)
{
    m_token=reply->rawHeader(QByteArray("Authorization"));
    getHttpRequst();
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
    QNetworkRequest request(QUrl(url.toString()+"cards"));

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

QString HttpRequest::getToken() const
{
    return m_token;
}




