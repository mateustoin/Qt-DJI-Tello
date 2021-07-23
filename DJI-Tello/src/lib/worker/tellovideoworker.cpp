#include "src/include/worker/tellovideoworker.h"

TelloVideoWorker::TelloVideoWorker(QObject *parent) : QObject(parent),
                                                      captureOpened(false),
                                                      videoUdpURL("udp://@0.0.0.0:11111"),
                                                      frameCounter(0) {
    videoCapture = new cv::VideoCapture();
    currentOpencvFrame = new cv::Mat();
}

TelloVideoWorker::~TelloVideoWorker() {

}

void TelloVideoWorker::startVideoStream() {
    if (startVideoConfig()){
        processVideoLoop();
    }
}

void TelloVideoWorker::escapeKeyPressed() {
    if (cv::waitKey(30) == 27) {
        closeVideoStream();
    }
}

void TelloVideoWorker::closeVideoStream() {
    cv::destroyAllWindows();
    captureOpened = false;
    videoCapture->release();
    frameCounter = 0;
    emit videoClosed();
}

bool TelloVideoWorker::startVideoConfig() {
    qInfo() << "Antes de abrir a captura de video";
    videoCapture->open(videoUdpURL.toStdString(), cv::CAP_GSTREAMER);
    qInfo() << "Depois de abrir a captura de video";
    cv::namedWindow("Video from Tello", CV_WINDOW_AUTOSIZE);

    if (!videoCapture->isOpened()) {
        captureOpened = false;
        emit videoCantOpen();
        return false;
    }else{
        captureOpened = true;
        emit videoOpened();
        return true;
    }
}

void TelloVideoWorker::processVideoLoop() {
    while (captureOpened) {
        videoCapture->read(*currentOpencvFrame);
        imshow("Video from Tello", *currentOpencvFrame);

        //getDecodeResultEveryNoFrames(20);
        //escapeKeyPressed();
    }
}
