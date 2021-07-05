#ifndef TELLOSTATEWORKER_H
#define TELLOSTATEWORKER_H

#include <QObject>

class TelloStateWorker : public QObject
{
    Q_OBJECT
public:
    explicit TelloStateWorker(QObject *parent = nullptr);

signals:

};

#endif // TELLOSTATEWORKER_H
