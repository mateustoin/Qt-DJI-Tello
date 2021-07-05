#ifndef TELLOSTATECONTROLLER_H
#define TELLOSTATECONTROLLER_H

#include <QObject>

class TelloStateController : public QObject
{
    Q_OBJECT
public:
    explicit TelloStateController(QObject *parent = nullptr);

signals:

};

#endif // TELLOSTATECONTROLLER_H
