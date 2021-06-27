#ifndef FRAMEDECODER_H
#define FRAMEDECODER_H

#include <QObject>
// https://github.com/ftylitak/qzxing
#include <QZXing.h>
#include "opencv2/opencv.hpp"

class FrameDecoder : public QObject {
    Q_OBJECT
public:
    explicit FrameDecoder(QObject *parent = nullptr);

signals:
    void imageDecoded();

public slots:
    QString decodeFrame(cv::Mat);

private:
    QZXing decoder;
    QImage qimageFrame;

    void decoderConfig();
};

#endif // FRAMEDECODER_H
