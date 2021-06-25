#include "tellocommand.h"

TelloCommand::TelloCommand(QObject *parent) : QObject(parent), localPort(2020),
                                                               telloCommandPort(8889),
                                                               telloAddress("192.168.10.1"),
                                                               currentResponse("")
{
    // Try to connect ninding a socket on port 2020
    // If return some error, dosen't connect
    if (!telloCommandSocket.bind(localPort)) {
        qInfo() << telloCommandSocket.errorString();
    }else{
        qInfo() << "Local bind ready on " << telloCommandSocket.localAddress() << ":" << telloCommandSocket.localPort();
    }
}

TelloCommand::~TelloCommand() {
    telloCommandSocket.close();
}

void TelloCommand::connect_tello() {
    telloConnection = send_control_command("command");

    if (telloConnection) {

    }
}

void TelloCommand::readResponse() {
    while (telloCommandSocket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloCommandSocket.receiveDatagram();
        qInfo() << "Drone response: " << datagram.data();
        currentResponse = datagram.data();
    }
}

bool TelloCommand::send_control_command(QString command) {
    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);
    QString response = "No response";
    for (int i=0; i<RETRY_COUNT; i++) {
        response = send_command_with_return(command);
        qInfo() << "Response: " << response;
        if (response == "ok")
            return true;
    }

    return false;
}

void TelloCommand::send_command_without_return(QString command) {
    // Sending command to tello without worrying about response
    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);
    telloCommandSocket.writeDatagram(data);
}

QString TelloCommand::send_command_with_return(QString command) {
    currentResponse = " ";

    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);

    QDateTime dateTime = QDateTime::currentDateTime();
    telloCommandSocket.writeDatagram(data);

    while (currentResponse != "error") {
        if (telloCommandSocket.hasPendingDatagrams()) {
            QByteArray response = telloCommandSocket.receiveDatagram().data();

            if (response != "error")
                return response;
            else
                return "error";
        }

        quint16 currentTime = QDateTime::currentDateTime().msecsTo(dateTime)*(-1);
        if (currentTime > RESPONSE_TIMEOUT) {
            return "error";
        }

        QThread::msleep(10);
    }

    return currentResponse;
}
