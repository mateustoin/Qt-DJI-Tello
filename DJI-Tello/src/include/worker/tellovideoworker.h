#ifndef TELLOVIDEOWORKER_H
#define TELLOVIDEOWORKER_H

#include <QObject>

class TelloVideoWorker : public QObject
{
    Q_OBJECT
public:
    explicit TelloVideoWorker(QObject *parent = nullptr);

signals:

};

#endif // TELLOVIDEOWORKER_H
