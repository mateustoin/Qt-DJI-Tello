#ifndef TELLOVIDEO_H
#define TELLOVIDEO_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <src/include/third_operation/framedecoder.h>

class QQmlEngine;
class QJSEngine;

class TelloVideo : public QObject {
    Q_OBJECT
public:
    static TelloVideo *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    ~TelloVideo();

public slots:
    void startVideoStream();

private slots:
    void escapeKeyPressed();
    void getDecodeResultEveryNoFrames(int);
    bool startVideoConfig();
    void processVideoLoop();

private:
    explicit TelloVideo(QObject *parent = nullptr);
    static TelloVideo* m_pThis;

    bool captureOpened;
    cv::VideoCapture *videoCapture;
    cv::Mat currentOpencvFrame;
    FrameDecoder decoder;
    QString videoUdpURL;

    quint32 frameCounter;

signals:
    void videoCantOpen();
    void videoClosed();
    void videoOpened();
    void newDecodeResult(QString);
};

#endif // TELLOVIDEO_H
