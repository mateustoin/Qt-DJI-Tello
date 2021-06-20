#ifndef TELLOVIDEO_H
#define TELLOVIDEO_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"

// https://github.com/ftylitak/qzxing
#include <QZXing.h>

class TelloVideo : public QObject {
    Q_OBJECT
public:
    explicit TelloVideo(QObject *parent = nullptr);
    ~TelloVideo();

public slots:
    void show_video();

private:
    bool showScreen;
    cv::VideoCapture *cap;
signals:

};

#endif // TELLOVIDEO_H
