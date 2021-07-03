#include "tellovideo.h"

TelloVideo::TelloVideo(QObject *parent) : QObject(parent), captureOpened(false),
                                                           videoUdpURL("udp://@0.0.0.0:11111"),
                                                           frameCounter(0){
    videoCapture = new cv::VideoCapture();
}

TelloVideo::~TelloVideo() {
    cv::destroyAllWindows();
    videoCapture->release();
    delete videoCapture;
}

void TelloVideo::startVideoStream() {
    if (startVideoConfig()){
        processVideoLoop();
    }
}

void TelloVideo::escapeKeyPressed() {
    /*
     * Wait for 'esc' key press for 30ms. If 'esc' key is
     * pressed, close everything related to video stream.
     */
    if (cv::waitKey(30) == 27) {
        cv::destroyAllWindows();
        captureOpened = false;
        videoCapture->release();
        frameCounter = 0;
        emit videoClosed();
    }
}

void TelloVideo::getDecodeResultEveryNoFrames(int no_frames) {
    /*
     * Every no_frames frames try to decode image and get the results
     */

    QString result = "";
    if (frameCounter%no_frames == 0){
         result = decoder.decodeFrame(currentOpencvFrame);

         if (result != ""){
             emit newDecodeResult(result);
         }
    }
    frameCounter++;
}

bool TelloVideo::startVideoConfig() {
    videoCapture->open(videoUdpURL.toStdString(), cv::CAP_GSTREAMER);
    cv::namedWindow("Tello Video", CV_WINDOW_AUTOSIZE);

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

void TelloVideo::processVideoLoop() {
    while (captureOpened) {
        videoCapture->read(currentOpencvFrame);
        imshow("Tello Video", currentOpencvFrame);

        getDecodeResultEveryNoFrames(20);
        escapeKeyPressed();
    }
}
