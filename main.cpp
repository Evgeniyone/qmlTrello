#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "noteslist.h"
#include "notesmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<NotesModel>("Notes",1,0,"NotesModel");
    qmlRegisterUncreatableType<NotesList>("Notes", 1, 0, "NotesList",
                                          QStringLiteral("NotesList should not be created in QML"));


    //NotesList notesList;

    QQmlApplicationEngine engine;
    //    engine.rootContext()->setContextProperty(QStringLiteral("notesList"),&notesList);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);

    return app.exec();
}
