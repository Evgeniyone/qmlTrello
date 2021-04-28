#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "notes_headers/noteslist.h"
#include "notes_headers/notesmodel.h"
#include "httprequest.h"
#include<vector>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<NotesModel>("Notes",1,0,"NotesModel");
    qmlRegisterUncreatableType<NotesList>("Notes", 1, 0, "NotesList",
                                          QStringLiteral("NotesList should not be created in QML"));


    NotesList notesList;
    HttpRequest request(&notesList);



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("notesList"),&notesList);
    engine.rootContext()->setContextProperty(QStringLiteral("httprequest"),&request);


    const QUrl url(QStringLiteral("qrc:/qml_sourse/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);

    return app.exec();
}
