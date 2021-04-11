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

void HttpRequest::getHttpRequst()
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(slotFinished(QNetworkReply*))
                );
    QNetworkRequest request(QUrl("http://192.168.31.52:8080/cards"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    //    accessManager->post(request,
    //                        "{\"name\":\"dw\"}"
    //                       );
    accessManager->get(request);

}

void HttpRequest::slotFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array=document.array();



    for(auto note:array){
        NotesItem item;
        QJsonObject subtree = note.toObject();
        item.description=subtree.value("name").toString();
        item.id=subtree.value("id").toInt();
        notes->appendItem(item);
    }

}

