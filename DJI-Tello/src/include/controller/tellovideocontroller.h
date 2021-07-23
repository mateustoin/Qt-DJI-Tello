#ifndef TELLOVIDEOCONTROLLER_H
#define TELLOVIDEOCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "opencv2/opencv.hpp"
#include <src/include/worker/tellovideoworker.h>
#include <src/include/third_operation/framedecoder.h>

Q_DECLARE_METATYPE(cv::Mat)

class TelloVideoController : public QObject {
    Q_OBJECT
public:
    explicit TelloVideoController(QObject *parent = nullptr);
    ~TelloVideoController();

public slots:
    void start();

    void openTelloVideoStream();
    void closeTelloVideoStream();
    bool videoIsOpen();

private slots:
    void setVideoOpen();
    void setVideoClose();

signals:
    void openVideoStream();
    void closeVideoStream();

private:
    QThread telloVideoThread;
    TelloVideoWorker *videoWorker;

    QThread frameDecoderThread;
    FrameDecoder *frameDecoder;

    bool isVideoOpen;
};

#endif // TELLOVIDEOCONTROLLER_H
