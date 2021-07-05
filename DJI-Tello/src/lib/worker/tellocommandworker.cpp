#include "src/include/worker/tellocommandworker.h"

TelloCommandWorker::TelloCommandWorker(QObject *parent) : QObject(parent),
                                                          localPort(2020),
                                                          telloCommandPort(8889),
                                                          telloAddress("192.168.10.1"),
                                                          currentResponse("")
{
    startCommandConfig();
}

TelloCommandWorker::~TelloCommandWorker() {
    telloCommandSocket.close();
}

void TelloCommandWorker::connectTello() {
    telloConnection = send_control_command("command");

    if (telloConnection)
        emit connectionWithTelloEstablished();
    else
        emit connectionWithTelloFailed();
}

void TelloCommandWorker::readResponse() {
    while (telloCommandSocket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloCommandSocket.receiveDatagram();
        currentResponse = datagram.data();
    }
}

bool TelloCommandWorker::send_control_command(QString command) {
    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);

    return sendCommandWithRetry(command);
}

void TelloCommandWorker::send_command_without_return(QString command) {
    // Sending command to tello without worrying about response
    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);
    telloCommandSocket.writeDatagram(data);
}

QString TelloCommandWorker::send_command_with_return(QString command) {
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

        //QThread::msleep(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return currentResponse;
}

void TelloCommandWorker::startCommandConfig() {
    /*
    * Try to connect a socket on port 2020
    * If return some error, print error msg
    */

    if (!telloCommandSocket.bind(localPort)) {
        emit connectionWithSocketFailed();
        qInfo() << telloCommandSocket.errorString();
    }else{
        qInfo() << "Local bind ready on " << telloCommandSocket.localAddress() << ":" << telloCommandSocket.localPort();
    }
}

bool TelloCommandWorker::sendCommandWithRetry(QString command) {
    QString response = "";
    for (int i=0; i<RETRY_COUNT; i++) {
        response = send_command_with_return(command);
        if (response != "error") {
            qInfo() << "Response: " << response;
            return true;
        }
    }
    return false;
}
