#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <tellocommand.h>
#include <tellostate.h>
#include <tellovideo.h>
#include <tello.h>

#include <QThread>

#include <QQmlContext>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QThread thread_video, thread_command, thread_state;

    TelloCommand *tello = new TelloCommand();
    TelloState *telloState = new TelloState();
    TelloVideo *telloVideo = new TelloVideo();

    qInfo() << "TelloCommand rodando na thread: " << tello->thread();
    qInfo() << "TelloVideo rodando na thread: " << telloVideo->thread();
    qInfo() << "TelloState rodando na thread: " << telloState->thread();

    tello->moveToThread(&thread_command);
    //telloState->moveToThread(&thread_state);
    telloVideo->moveToThread(&thread_video);

    qInfo() << "TelloCommand rodando na thread: " << tello->thread();
    qInfo() << "TelloVideo rodando na thread: " << telloVideo->thread();
    qInfo() << "TelloState rodando na thread: " << telloState->thread();

    //engine.setObjectOwnership(tello, QQmlEngine::CppOwnership);
    engine.rootContext()->setContextProperty("Tello", tello);
    engine.rootContext()->setContextProperty("TelloState", telloState);
    engine.rootContext()->setContextProperty("TelloVideo", telloVideo);

    const QUrl url(QStringLiteral("qrc:/user_interface/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
