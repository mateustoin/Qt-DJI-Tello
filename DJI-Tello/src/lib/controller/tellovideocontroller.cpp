#include "src/include/controller/tellovideocontroller.h"

TelloVideoController::TelloVideoController(QObject *parent) : QObject(parent),
                                                              isVideoOpen(false){
    videoWorker = new TelloVideoWorker();
    videoWorker->moveToThread(&telloVideoThread);

    connect(this, &TelloVideoController::openVideoStream,
            videoWorker, &TelloVideoWorker::startVideoStream, Qt::QueuedConnection);
    connect(this, &TelloVideoController::closeVideoStream,
            videoWorker, &TelloVideoWorker::closeVideoStream, Qt::QueuedConnection);

    connect(videoWorker, &TelloVideoWorker::videoOpened,
            this, &TelloVideoController::setVideoOpen, Qt::QueuedConnection);
    connect(videoWorker, &TelloVideoWorker::videoClosed,
            this, &TelloVideoController::setVideoClose, Qt::QueuedConnection);

    frameDecoder = new FrameDecoder();
    frameDecoder->moveToThread(&frameDecoderThread);
    qRegisterMetaType< cv::Mat >("cv::Mat");

    connect(&frameDecoderThread, &QThread::started,
            frameDecoder, &FrameDecoder::startDecoderConfig, Qt::QueuedConnection);
    connect(videoWorker, &TelloVideoWorker::newFrameToDecode,
            frameDecoder, &FrameDecoder::decodeFrame);
    start();
}

TelloVideoController::~TelloVideoController() {
    qInfo() << "Destrutor de TelloVideoController acionado!";

    telloVideoThread.quit();
    telloVideoThread.wait();
}

void TelloVideoController::start() {
    telloVideoThread.start();
    frameDecoderThread.start();
}

void TelloVideoController::openTelloVideoStream() {
    emit openVideoStream();
}

void TelloVideoController::closeTelloVideoStream() {
    emit closeVideoStream();
}

bool TelloVideoController::videoIsOpen() {
    return isVideoOpen;
}

void TelloVideoController::setVideoOpen() {
    this->isVideoOpen = true;
}

void TelloVideoController::setVideoClose() {
    this->isVideoOpen = false;
}
