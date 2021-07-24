#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/include/controller/tellocommandcontroller.h>
#include <src/include/controller/tellostatecontroller.h>
#include <src/include/controller/tellovideocontroller.h>
#include <QQmlContext>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TelloCommandController *telloCommand = new TelloCommandController();
    TelloStateController *telloState = new TelloStateController();
    TelloVideoController *telloVideo = new TelloVideoController();

    engine.rootContext()->setContextProperty("Tello", telloCommand);
    engine.rootContext()->setContextProperty("TelloState", telloState);
    engine.rootContext()->setContextProperty("TelloVideo", telloVideo);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
