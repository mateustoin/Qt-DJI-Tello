#include "tellovideo.h"

TelloVideo::TelloVideo(QObject *parent) : QObject(parent), showScreen(true) {
    cap = new cv::VideoCapture();
}

TelloVideo::~TelloVideo() {
    qInfo() << "Video closed";
}

void TelloVideo::show_video() {
    cap->open("udp://@0.0.0.0:11111", cv::CAP_GSTREAMER);
    cv::Mat frame;
    cv::namedWindow("Tello Video", CV_WINDOW_AUTOSIZE);

    if (!cap->isOpened()) {  // if not success, exit program
        qInfo() << "Capture not open";
        this->showScreen = false;
    }else{
        while (this->showScreen) {
            cap->read(frame);

            imshow("Tello Video", frame);
            if (cv::waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                //this->showScreen = false;
                cv::destroyAllWindows();
                cap->release();
                qInfo() << "esc key is pressed by user";
                break;
                //exit(0);
            }
        }
    }
}
