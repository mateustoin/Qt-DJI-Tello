#include "tellovideo.h"

TelloVideo::TelloVideo(QObject *parent) : QObject(parent), showScreen(true) {
    cap = new cv::VideoCapture();
}

TelloVideo::~TelloVideo() {
    qInfo() << "Video closed";
}

void TelloVideo::show_video() {
    QZXing decoder;
    QImage img;
    //decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
    decoder.setDecoder( QZXing::DecoderFormat_CODE_128);
    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);

    cap->open("udp://@0.0.0.0:11111", cv::CAP_GSTREAMER);
    cv::Mat frame;
    cv::namedWindow("Tello Video", CV_WINDOW_AUTOSIZE);
    quint32 counter = 0;
    if (!cap->isOpened()) {  // if not success, exit program
        qInfo() << "Capture not open";
        this->showScreen = false;
    }else{
        while (this->showScreen) {
            cap->read(frame);

            if (counter%20 == 0){
                img = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            }

            QString result = decoder.decodeImage(img);
            if (result != ""){
                qInfo() << "Result(" << counter << "): " << result;
            }

            imshow("Tello Video", frame);
            if (cv::waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                //this->showScreen = false;
                cv::destroyAllWindows();
                cap->release();
                qInfo() << "esc key is pressed by user";
                break;
                //exit(0);
            }
            img = QImage();
            counter++;
        }
    }
}
