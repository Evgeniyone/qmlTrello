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
    url="http://62.77.153.231:8888/";
    timestamp=0;
}

TableList *HttpRequest::list() const
{
    return tables;
}



void HttpRequest::sendNote(int indexOfNote,int indexOfTable)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);


    TableItem *tableItem = &((*tables->items())[indexOfTable]);
    NotesItem *noteItem=&(*tableItem->list->items())[indexOfNote];

    QNetworkRequest request(QUrl(url.toString()+"cards"
                                 +"/"+QString::number(tableItem->id)));
    
    
    QJsonObject auref;

    connect(accessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        sendNoteFinished(reply,noteItem);
    });

    auref["name"]=noteItem->description;

    
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    QJsonDocument doc(auref);
    QByteArray data = doc.toJson();
    if(noteItem->status==Status::Created)
    {
        accessManager->post(request,data);

        noteItem->status=Status::Sended;

    }
    else
    {

        QString m=url.toString()+"cards/"+QString::number(tableItem->id)
                +"/"+QString::number(noteItem->id);
        qDebug()<<m;
        QNetworkRequest request(QUrl(m.toUtf8()));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
        QJsonObject auref;
        auref["name"]=noteItem->description;
        QJsonDocument doc(auref);
        QByteArray data = doc.toJson();
        accessManager->put(request,data);
    }
}

void HttpRequest::sendNoteFinished(QNetworkReply *reply,NotesItem*item)
{
    QByteArray data= reply->readAll();
    item->id=data.toInt();

    qDebug()<<item->id;

}



void HttpRequest::sinchronize()
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    QNetworkRequest request(QUrl(url.toString()+"cards/"+"sinch?timestamp="+QString::number(timestamp)));
    connect(
                accessManager,
                SIGNAL(finished(QNetworkReply*)),
                this,
                SLOT(sinchronizeFinished(QNetworkReply*))
                );
    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    accessManager->get(request);
}
void HttpRequest::sinchronizeFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray arrayOfTable= document.array();
    reply->rawHeader(QByteArray("Authorization"));



    for (auto table : arrayOfTable){
        TableItem itemOfTable;
        QJsonObject subtree = table.toObject();

        auto firstTable =tables->items()->begin();
        auto end = tables->items()->end();

        itemOfTable.id = subtree.value("id").toInt();
        itemOfTable.name = subtree.value("name").toString();
        itemOfTable.list = new NotesList();

        QString statusOfTable = subtree.value("status").toString();
        QJsonArray arrayOfNote = subtree.value("cards").toArray();

        auto findedTable=std::find_if
                (firstTable, end, [=](TableItem n_item)
        {
            return (itemOfTable.id==n_item.id?true:false);

        });

        if (findedTable == end){
            for (auto note : arrayOfNote){
                QJsonObject object = note.toObject();
                NotesItem item;
                item.description = object.value("name").toString();
                item.id = object.value("id").toInt();
                QString statusOfNote = object.value("status").toString();

                if (statusOfNote != "DELETED"){
                    item.status = Status::Sended;
                    itemOfTable.list->appendItem(item);
                }
            }
            tables->appendItem(itemOfTable);
        }
        else{


            auto firstNote = findedTable->list->items()->begin();
            auto endNote = findedTable->list->items()->end();

            for (auto note : arrayOfNote){
                QJsonObject object = note.toObject();

                NotesItem item;
                item.description=object.value("name").toString();
                item.id= object.value("id").toInt();

                QString statusOfNote = object.value("status").toString();

                auto finded_node=std::find_if
                        (firstNote, endNote, [=](NotesItem n_item)
                {
                    return (item.id==n_item.id?true:false);

                });

                int indexOfNote=finded_node-firstNote;
                if (finded_node==endNote && statusOfNote!="DELETED")
                {
                    findedTable->list->appendItem(item);
                    qDebug()<<item.id;
                }

                if (finded_node!=endNote && statusOfNote!="DELETED")

                {
                    findedTable->list->changeItem(indexOfNote,item);

                }


                if(statusOfNote=="DELETED" && finded_node!=endNote)
                {
                    qDebug()<<finded_node->id;
                    findedTable->list->deleteItem(finded_node);
                }
            }
        }
    }
    timestamp=QDateTime::currentMSecsSinceEpoch();
}
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

void HttpRequest::deleteNote(int indexOfNote,int indexOfTable)
{
    QNetworkAccessManager *accessManager=new QNetworkAccessManager (this);
    TableItem *tableItem = &((*tables->items())[indexOfTable]);
    NotesItem *noteItem=&(*tableItem->list->items())[indexOfNote];

    QNetworkRequest request(QUrl(url.toString()+"cards/"
                                 +QString::number(tableItem->id)
                                 +"/"+QString::number(noteItem->id)));

    connect(accessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        deleteNoteFinished(reply,indexOfTable,indexOfNote);
    });

    request.setRawHeader(QByteArray("Authorization"),m_token.toUtf8());
    accessManager->deleteResource(request);
}

void HttpRequest::deleteNoteFinished(QNetworkReply *, int indexOfTable,int indexOfNote)
{
    (*tables->items())[indexOfTable].list->deleteItem(indexOfNote);
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





