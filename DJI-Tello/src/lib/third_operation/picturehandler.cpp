#include "src/include/third_operation/picturehandler.h"
#include <QDebug>

PictureHandler::PictureHandler(QObject *parent) : QObject(parent) {

}

void PictureHandler::updateCurrentFrame(cv::Mat frame) {
    currentOpencvFrame = frame;
}

void PictureHandler::saveCurrentFrameOnDisk() {
    QDateTime fileCreationDateTime;
    QString nameComplement = fileCreationDateTime.currentDateTime().toString("h:m:s ap");
    QString filePath = QDir::currentPath() + "/tello-data-" + nameComplement + ".jpg";
    cv::imwrite(filePath.toStdString(), currentOpencvFrame);
}
