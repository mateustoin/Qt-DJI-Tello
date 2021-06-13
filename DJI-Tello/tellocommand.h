#ifndef TELLOCOMMAND_H
#define TELLOCOMMAND_H

/*
 * Code based on this repository: https://github.com/damiafuentes/DJITelloPy
 */

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>

class TelloCommand : public QObject
{
    Q_OBJECT
public:
    explicit TelloCommand(QObject *parent = nullptr);
    ~TelloCommand();

public:
    void send_command_without_return();
    void send_command_with_return();

public slots:
    void connect_tello();
    void readResponse();
    void send_control_command(QString);

signals:
    void connected();

private:
    quint16 localPort;
    quint16 telloCommandPort;
    QHostAddress telloAddress;
    QUdpSocket telloCommandSocket;
};

#endif // TELLOCOMMAND_H
