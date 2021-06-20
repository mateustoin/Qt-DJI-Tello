#ifndef TELLOCOMMAND_H
#define TELLOCOMMAND_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QThread>
#include <QTimer>

class TelloCommand : public QObject {
    Q_OBJECT
public:
    explicit TelloCommand(QObject *parent = nullptr);
    ~TelloCommand();

public:

public slots:
    void connect_tello();
    void readResponse();

    bool send_control_command(QString);
    void send_command_without_return(QString);
    QString send_command_with_return(QString);

signals:
    void connected();

private:
    quint16 localPort;
    quint16 telloCommandPort;
    QHostAddress telloAddress;
    QUdpSocket telloCommandSocket;

    const quint8 REPS = 20;            // 20 tentatives
    const quint8 RETRY_COUNT = 3;      // 3 tentatives
    const quint16 RESPONSE_TIMEOUT = 2000; // 2 seconds -> 2000 ms
    QByteArray currentResponse;

    bool telloConnection;
    QTimer keepAliveTimer;
    QThread connectedThread;
};

#endif // TELLOCOMMAND_H
