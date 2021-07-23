#include "src/include/third_operation/framedecoder.h"

FrameDecoder::FrameDecoder(QObject *parent) : QObject(parent) {
    //startDecoderConfig();
}

void FrameDecoder::decodeFrame(cv::Mat frame) {
    qimageFrame = QImage((uchar*) frame.data,
                                  frame.cols,
                                  frame.rows,
                                  frame.step,
                                  QImage::Format_RGB888);

    QString result = decoder.decodeImage(qimageFrame);
    if (result != ""){
        qInfo() << "Frame decodificado: " << result;
    }
}

void FrameDecoder::startDecoderConfig() {
    decoder.setDecoder( QZXing::DecoderFormat_CODE_128);
    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);
}
