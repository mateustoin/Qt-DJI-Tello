#ifndef TELLOVIDEO_H
#define TELLOVIDEO_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <third_operations/framedecoder.h>

class TelloVideo : public QObject {
    Q_OBJECT
public:
    explicit TelloVideo(QObject *parent = nullptr);
    ~TelloVideo();

public slots:
    void startVideoStream();

private slots:
    void escapeKeyPressed();
    void getDecodeResultEveryNoFrames(int);
    bool startVideoConfig();
    void processVideoLoop();

private:
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
