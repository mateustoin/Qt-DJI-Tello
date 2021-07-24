#ifndef PICTUREHANDLER_H
#define PICTUREHANDLER_H

#include <QObject>
#include <QDir>
#include <QDateTime>
#include "opencv2/opencv.hpp"

class PictureHandler : public QObject {
    Q_OBJECT
public:
    explicit PictureHandler(QObject *parent = nullptr);

public slots:
    void updateCurrentFrame(cv::Mat);
    void saveCurrentFrameOnDisk();


private:
    cv::Mat currentOpencvFrame;

signals:

};

#endif // PICTUREHANDLER_H
