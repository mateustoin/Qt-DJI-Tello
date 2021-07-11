#ifndef TELLOCOMMANDWORKER_H
#define TELLOCOMMANDWORKER_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QThread>
#include <TelloEnumTypes.h>

class TelloCommandWorker : public QObject {
    Q_OBJECT
public:
    explicit TelloCommandWorker(QObject *parent = nullptr);
    ~TelloCommandWorker();

public slots:
    void connectTello();
    void readResponse();

    bool send_control_command(QString);
    void send_command_without_return(QString);
    QString send_command_with_return(QString);

    void startCommandConfig();

private slots:
    bool sendCommandWithRetry(QString);

signals:
    void alertSignal(TelloAlerts);
    void responseSignal(TelloResponse, QString);
    void readyCommandResponse(QString);

private:
    quint16 localPort;
    quint16 telloCommandPort;
    QHostAddress telloAddress;
    QUdpSocket *telloCommandSocket = nullptr;

    const quint8 REPS = 20;            // 20 tentatives
    const quint8 RETRY_COUNT = 3;      // 3 tentatives
    const quint16 RESPONSE_TIMEOUT = 1000; // 1 second -> 1000 ms
    QByteArray currentResponse;

    bool telloConnection;
    QThread connectedThread;
};

#endif // TELLOCOMMANDWORKER_H
