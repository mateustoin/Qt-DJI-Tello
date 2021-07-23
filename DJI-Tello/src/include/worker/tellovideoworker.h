#ifndef TELLOVIDEOWORKER_H
#define TELLOVIDEOWORKER_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"

class TelloVideoWorker : public QObject
{
    Q_OBJECT
public:
    explicit TelloVideoWorker(QObject *parent = nullptr);
    ~TelloVideoWorker();

public slots:
    void startVideoStream();
    void closeVideoStream();

private slots:
    void escapeKeyPressed();
    //void getDecodeResultEveryNoFrames(int);
    void emitFrameEveryNoFrames();
    bool startVideoConfig();
    void processVideoLoop();

private:
    bool captureOpened;
    cv::VideoCapture *videoCapture;
    cv::Mat *currentOpencvFrame;
    //FrameDecoder decoder;
    QString videoUdpURL;

    quint32 frameCounter;
    const int NO_FRAMES_TO_SEND = 5;

signals:
    void videoOpened();
    void videoClosed();
    void videoCantOpen();
    void newFrameToDecode(cv::Mat);
};

#endif // TELLOVIDEOWORKER_H
