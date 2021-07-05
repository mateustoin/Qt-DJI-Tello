#ifndef TELLOVIDEOCONTROLLER_H
#define TELLOVIDEOCONTROLLER_H

#include <QObject>

class TelloVideoController : public QObject
{
    Q_OBJECT
public:
    explicit TelloVideoController(QObject *parent = nullptr);

signals:

};

#endif // TELLOVIDEOCONTROLLER_H
