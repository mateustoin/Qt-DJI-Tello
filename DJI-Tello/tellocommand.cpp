#include "tellocommand.h"

TelloCommand::TelloCommand(QObject *parent) : QObject(parent), localPort(2020), telloCommandPort(8889),
                                                               telloAddress("192.168.10.1")
{
    connect(&telloCommandSocket, &QUdpSocket::readyRead, this, &TelloCommand::readResponse);
}

TelloCommand::~TelloCommand() {
    telloCommandSocket.close();
}

void TelloCommand::connect_tello() {
    if (!telloCommandSocket.bind(localPort)) {
        qInfo() << telloCommandSocket.errorString();
        return;
    }

    qInfo() << "Connection with tello ready on " << telloCommandSocket.localAddress() << ":" << telloCommandSocket.localPort();
}

void TelloCommand::readResponse() {
    while (telloCommandSocket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloCommandSocket.receiveDatagram();
        qInfo() << "Drone response: " << datagram.data();
    }
}

void TelloCommand::send_control_command(QString command) {
    QByteArray commandData = command.toLatin1();

    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);
    telloCommandSocket.writeDatagram(data);
    qInfo() << "Command sent: " << command;
}
