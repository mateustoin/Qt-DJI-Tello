#include "framedecoder.h"

FrameDecoder::FrameDecoder(QObject *parent) : QObject(parent) {
    decoderConfig();
}

QString FrameDecoder::decodeFrame(cv::Mat frame) {
    qimageFrame = QImage((uchar*) frame.data,
                                  frame.cols,
                                  frame.rows,
                                  frame.step,
                                  QImage::Format_RGB888);

    QString result = decoder.decodeImage(qimageFrame);

    return result;
}

void FrameDecoder::decoderConfig() {
    decoder.setDecoder( QZXing::DecoderFormat_CODE_128);
    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);
}
