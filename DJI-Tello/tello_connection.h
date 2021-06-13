#ifndef TELLO_CONNECTION_H
#define TELLO_CONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QThread>
#include <qqml.h>

class Tello_Connection : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Tello_Connection(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void stop();
    void timeout();
    void readyRead();
    void broadcast();

private:
    QUdpSocket socket;
    quint16 port;
    quint16 telloPort;
    QHostAddress telloAddress;

    QThread m_workerThread;
    QTimer timer;
};

#endif // TELLO_CONNECTION_H
