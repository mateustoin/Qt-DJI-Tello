#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <tellocommand.h>
#include <tellostate.h>
#include <tellovideo.h>

#include <QQmlContext>
#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    Mat image = imread("/home/mateus/Imagens/download.png");
//    imshow("Output", image);

    TelloCommand *tello = new TelloCommand();
    TelloState *telloState = new TelloState();
    TelloVideo *telloVideo = new TelloVideo();
    //engine.setObjectOwnership(tello, QQmlEngine::CppOwnership);
    engine.rootContext()->setContextProperty("Tello", tello);
    engine.rootContext()->setContextProperty("TelloState", telloState);
    engine.rootContext()->setContextProperty("TelloVideo", telloVideo);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
