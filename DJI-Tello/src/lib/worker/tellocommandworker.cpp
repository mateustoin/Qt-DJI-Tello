#include "src/include/worker/tellocommandworker.h"

TelloCommandWorker::TelloCommandWorker(QObject *parent) : QObject(parent),
                                                          localPort(2020),
                                                          telloCommandPort(8889),
                                                          telloAddress("192.168.10.1"),
                                                          currentResponse("")
{
}

TelloCommandWorker::~TelloCommandWorker() {
    telloCommandSocket->close();
}

void TelloCommandWorker::readResponse() {
    while (telloCommandSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloCommandSocket->receiveDatagram();
        currentResponse = datagram.data();

        triggerSignalBasedOnResponse(currentResponse);
    }
}

void TelloCommandWorker::send_command_without_return(QString command) {
    // Sending command to tello without worrying about response
    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);
    telloCommandSocket->writeDatagram(data);
}

QString TelloCommandWorker::send_command_with_return(QString command) {
    currentResponse = " ";

    QByteArray commandData = command.toLatin1();
    QNetworkDatagram data(commandData, telloAddress, telloCommandPort);

    QDateTime dateTime = QDateTime::currentDateTime();
    telloCommandSocket->writeDatagram(data);

    while (currentResponse == " ") {
        while (telloCommandSocket->hasPendingDatagrams()) {
            QByteArray response = telloCommandSocket->receiveDatagram().data();

            if (response != " "){
                return response;
            }
        }

        quint16 currentTime = QDateTime::currentDateTime().msecsTo(dateTime)*(-1);
        if (currentTime > RESPONSE_TIMEOUT) {
            return "timeout";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return "undefined_behavior";
}

void TelloCommandWorker::startCommandConfig() {
    /*
    * Try to connect a socket on port 2020
    * If return some error, print error msg
    */
    telloCommandSocket = new QUdpSocket();
    if (!telloCommandSocket->bind(localPort)) {
        emit alertSignal(TelloAlerts::SOCKET_CONNECTION_FAILED);
        qInfo() << telloCommandSocket->errorString();
    }else{
        qInfo() << "Local bind ready on " << telloCommandSocket->localAddress() << ":" << telloCommandSocket->localPort();
        connect(telloCommandSocket, &QUdpSocket::readyRead,
                this, &TelloCommandWorker::readResponse);
    }
}

void TelloCommandWorker::triggerSignalBasedOnResponse(QString response) {
    if (response == "timeout"){
        emit responseSignal(TelloResponse::TIMEOUT, response);
    }else if (response == "error"){
        emit responseSignal(TelloResponse::ERROR, response);
    }else if (response == "ok"){
        emit responseSignal(TelloResponse::OK, response);
    }else if (response.contains("\r\n")){
        emit responseSignal(TelloResponse::VALUE, response);
    }else if (response == "out of range"){
        emit responseSignal(TelloResponse::OUT_OF_RANGE, response);
    }else{
        emit responseSignal(TelloResponse::UNDEFINED, response);
    }
}

void TelloCommandWorker::send_control_command(QString command) {
    QString response = "";
//    for (int i=0; i<RETRY_COUNT; i++) {
//        response = send_command_with_return(command);
//        if (response == "timeout" && i==(RETRY_COUNT-1)){
//            emit responseSignal(TelloResponse::TIMEOUT, response);
//        }else if (response == "error" && i==(RETRY_COUNT-1)){
//            emit responseSignal(TelloResponse::ERROR, response);
//        }else if (response == "ok"){
//            emit responseSignal(TelloResponse::OK, response);
//            break;
//        }else if (response.contains("\r\n")){
//            emit responseSignal(TelloResponse::VALUE, response);
//            break;
//        }else if (i==(RETRY_COUNT-1)){
//            emit responseSignal(TelloResponse::UNDEFINED, response);
//        }
//    }

    response = send_command_with_return(command);
    if (response == "timeout"){
        emit responseSignal(TelloResponse::TIMEOUT, response);
    }else if (response == "error"){
        emit responseSignal(TelloResponse::ERROR, response);
    }else if (response == "ok"){
        emit responseSignal(TelloResponse::OK, response);
    }else if (response.contains("\r\n")){
        emit responseSignal(TelloResponse::VALUE, response);
    }else{
        emit responseSignal(TelloResponse::UNDEFINED, response);
    }

    //send_command_without_return(command);
}
