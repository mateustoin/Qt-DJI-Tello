#ifndef TELLOSTATE_H
#define TELLOSTATE_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>

class TelloState : public QObject
{
    Q_OBJECT
public:
    explicit TelloState(QObject *parent = nullptr);
    ~TelloState();

public slots:
    void connectStateServer();
    void readState();
    QString getCurrentState();

signals:

private:
    quint16 statePort;
    QHostAddress telloStateAddress;
    QUdpSocket telloStateServer;

    QByteArray currentState;
};

#endif // TELLOSTATE_H
