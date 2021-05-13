#include "httprequest.h"

#include <QNetworkRequest>
#include <QtNetwork>
#include <QDebug>
#include <algorithm>


HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{
    timestamp=0;
    
}

HttpRequest::HttpRequest(TableList *nlist):tables(nlist)
{
    url="http://192.168.31.104:8080/";
    timestamp=0;
}

TableList *HttpRequest::list() const
{
    return tables;
}



//void HttpRequest::sendNote(int index)
//{
//    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
//    QNetworkRequest request(QUrl(url.toString()+"cards"));
    
    
//    QJsonObject auref;
//    NotesItem *item=&(*notes->items())[index];
//    connect(accessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
//    {
//        sendNoteFinished(reply,item);
//    });

//    auref["name"]=item->description;
//    auref["numberOfList"]=1;
//    auref["pos"]=1;
    
//    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
//    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
//    QJsonDocument doc(auref);
//    QByteArray data = doc.toJson();
//    if(item->status==Status::Created)
//    {
//        accessManager->post(request,data);

//        item->status=Status::Sended;

//    }
//    else
//    {

//        QString m=url.toString()+"cards/"+QString::number(item->id);
//        qDebug()<<m;
//        QNetworkRequest request(QUrl(m.toUtf8()));
//        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
//        request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
//        QJsonObject auref;
//        auref["name"]=item->description;
//        QJsonDocument doc(auref);
//        QByteArray data = doc.toJson();
//        accessManager->put(request,data);
//    }
//}

//void HttpRequest::sendNoteFinished(QNetworkReply *reply,NotesItem*item)
//{
//    QByteArray data= reply->readAll();
//    item->id=data.toInt();

//    qDebug()<<item->id;

//}

//void HttpRequest::sinchronize()
//{
//    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
//    QNetworkRequest request(QUrl(url.toString()+"cards/"+"sinch?timestamp="+QString::number(timestamp)));
//    connect(
//                accessManager,
//                SIGNAL(finished(QNetworkReply*)),
//                this,
//                SLOT(sinchronizeFinished(QNetworkReply*))
//                );
//    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
//    accessManager->get(request);
//}

//void HttpRequest::sinchronizeFinished(QNetworkReply *reply)
//{
//    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
//    QJsonArray array=document.array();
//    reply->rawHeader(QByteArray("Authorization"));

//    auto first=notes->items()->begin();
//    auto end = notes->items()->end();
//    for(auto note:array){
//        NotesItem item;
//        QJsonObject subtree = note.toObject();
//        item.description=subtree.value("name").toString();
//        item.id=subtree.value("id").toInt();
//        QString status=subtree.value("status").toString();
//        auto finded_node=std::find_if
//                (first, end, [=](NotesItem n_item)
//        {
//            return (item.id==n_item.id?true:false);

//        });
//        int index=finded_node-first;

//        if (finded_node==end && status!="DELETED")
//        {
//            notes->appendItem(item);
//            qDebug()<<item.id;
//        }

//        if (finded_node!=end && status!="DELETED")

//        {
//            notes->changeItem(index,item);

//        }


//        if(status=="DELETED" && finded_node!=end)
//        {
//            qDebug()<<finded_node->id;
//            notes->deleteItem(finded_node);
//        }
//    }
//    timestamp=QDateTime::currentMSecsSinceEpoch();
//}

//void HttpRequest::deleteNote(int index)
//{
//    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
//    NotesItem *item=&(*notes->items())[index];
//    QNetworkRequest request(QUrl(url.toString()+"cards/"+QString::number(item->id)));
//    connect(accessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
//    {
//        deleteNoteFinished(reply,item);
//    });

//    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
//    accessManager->deleteResource(request);
//}

//void HttpRequest::deleteNoteFinished(QNetworkReply *, NotesItem *item)
//{
//    notes->deleteItem(item);
//}



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

    for(auto table:array){
        TableItem item;
        QJsonObject subtree = table.toObject();
        QJsonArray ar=subtree["cards"].toArray();
        item.name=subtree.value("name").toString();
        item.id=subtree.value("id").toInt();
        item.list=new NotesList();
        for(auto card:ar){
            QJsonObject object = card.toObject();
            NotesItem mItem;
            mItem.description=object.value("name").toString();
            mItem.id=object.value("id").toInt();

            item.list->appendItem(mItem);
        }
        tables->appendItem(item);

    }

}

QString HttpRequest::getToken() const
{
    return m_token;
}





