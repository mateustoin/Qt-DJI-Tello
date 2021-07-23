#ifndef FRAMEDECODER_H
#define FRAMEDECODER_H

#include <QObject>
// https://github.com/ftylitak/qzxing
#include <QZXing.h>
#include <QDebug>
#include "opencv2/opencv.hpp"

class FrameDecoder : public QObject {
    Q_OBJECT
public:
    explicit FrameDecoder(QObject *parent = nullptr);

signals:
    void imageDecoded();

public slots:
    void startDecoderConfig();
    void decodeFrame(cv::Mat);

//private slots:


private:
    QZXing decoder;
    QImage qimageFrame;
};

#endif // FRAMEDECODER_H
