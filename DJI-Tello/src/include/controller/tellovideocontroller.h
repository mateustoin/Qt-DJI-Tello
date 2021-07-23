#ifndef TELLOVIDEOCONTROLLER_H
#define TELLOVIDEOCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <src/include/worker/tellovideoworker.h>

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

    bool isVideoOpen;
};

#endif // TELLOVIDEOCONTROLLER_H
