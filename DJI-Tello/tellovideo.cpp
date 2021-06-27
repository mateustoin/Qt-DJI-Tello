#include "tellovideo.h"

TelloVideo::TelloVideo(QObject *parent) : QObject(parent), videoUdpURL("udp://@0.0.0.0:11111"),
                                                           frameCounter(0){
    cap = new cv::VideoCapture();
}

TelloVideo::~TelloVideo() {
    cv::destroyAllWindows();
    cap->release();
    delete cap;
}

void TelloVideo::show_video() {
    cap->open(videoUdpURL.toStdString(), cv::CAP_GSTREAMER);
    cv::namedWindow("Tello Video", CV_WINDOW_AUTOSIZE);
    qInfo() << "Video iniciando rodando na thread: " << this->thread();
    if (!cap->isOpened()) {  // if not success, exit program
        qInfo() << "Capture not open";
        emit videoCantOpen();
    }else{
        emit videoOpened();

        while (cap->isOpened()) {
            cap->read(currentOpencvFrame);

            QString result = "";
            if (frameCounter%20 == 0){
                 result = decoder.decodeFrame(currentOpencvFrame);

                 if (result != ""){
                     qInfo() << "Result(" << frameCounter << "): " << result;
                 }
            }

            imshow("Tello Video", currentOpencvFrame);
            if (cv::waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                cv::destroyAllWindows();
                cap->release();
                qInfo() << "ESC key is pressed by user";
                frameCounter = 0;
                break;
            }
            frameCounter++;
        }

        emit videoClosed();
    }
}
