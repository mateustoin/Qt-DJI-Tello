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

    pictureHandler = new PictureHandler();
    pictureHandler->moveToThread(&pictureHandlerThread);

    connect(this, &TelloVideoController::takePictureFromVideoStream,
            pictureHandler, &PictureHandler::saveCurrentFrameOnDisk, Qt::QueuedConnection);
    connect(videoWorker, &TelloVideoWorker::newFrame,
            pictureHandler, &PictureHandler::updateCurrentFrame, Qt::QueuedConnection);

    start();
}

TelloVideoController::~TelloVideoController() {
    telloVideoThread.quit();
    frameDecoderThread.quit();
    pictureHandlerThread.quit();

    telloVideoThread.wait();
    frameDecoderThread.wait();
    pictureHandlerThread.wait();
}

void TelloVideoController::start() {
    telloVideoThread.start();
    frameDecoderThread.start();
    pictureHandlerThread.start();
}

void TelloVideoController::openTelloVideoStream() {
    emit openVideoStream();
}

void TelloVideoController::closeTelloVideoStream() {
    emit closeVideoStream();
    videoWorker->setCaptureOpened(false);
}

void TelloVideoController::takePicture() {
    emit takePictureFromVideoStream();
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
