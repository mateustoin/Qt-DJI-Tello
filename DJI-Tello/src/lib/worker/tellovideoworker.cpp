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
        emit videoOpened();
        processVideoLoop();
    }
}

void TelloVideoWorker::escapeKeyPressed() {
    if (cv::waitKey(30) == 27) {
        closeVideoStream();
    }
}

void TelloVideoWorker::emitFrameEveryNoFrames() {
    if (frameCounter%NO_FRAMES_TO_SEND == 0){
        emit newFrameToDecode(*currentOpencvFrame);
        frameCounter = 0;
    }
    frameCounter++;
}

void TelloVideoWorker::closeVideoStream() {
    captureOpened = false;
    videoCapture->release();
    cv::destroyWindow("Video from Tello");
    cv::destroyAllWindows();
    emit videoClosed();
}

bool TelloVideoWorker::startVideoConfig() {
    videoCapture->open(videoUdpURL.toStdString(), cv::CAP_GSTREAMER);
    qInfo() << "Depois de abrir a captura de video";
    cv::namedWindow("Video from Tello", CV_WINDOW_AUTOSIZE);

    if (!videoCapture->isOpened()) {
        captureOpened = false;
        emit videoCantOpen();
        return false;
    }else{
        captureOpened = true;
        return true;
    }
}

void TelloVideoWorker::processVideoLoop() {
    while (captureOpened) {
        videoCapture->read(*currentOpencvFrame);
        imshow("Video from Tello", *currentOpencvFrame);
        emitFrameEveryNoFrames();
        //getDecodeResultEveryNoFrames(20);
        //escapeKeyPressed();
    }
}
