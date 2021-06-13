#include "tellostate.h"

TelloState::TelloState(QObject *parent) : QObject(parent), statePort(8890), telloStateAddress("0.0.0.0") {

}

TelloState::~TelloState() {
    telloStateServer.close();
}

void TelloState::connectStateServer() {
    if (!telloStateServer.bind(telloStateAddress ,statePort)) {
        qInfo() << telloStateServer.errorString();
        return;
    }else{
        connect(&telloStateServer, &QUdpSocket::readyRead, this, &TelloState::readState);
    }
}

void TelloState::readState() {
    while (telloStateServer.hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloStateServer.receiveDatagram();
        currentState = datagram.data();
        //qInfo() << "Drone response: " << datagram.data();
    }
}

QString TelloState::getCurrentState() {
    return currentState;
}
