#include "src/include/worker/tellostateworker.h"

TelloStateWorker::TelloStateWorker(QObject *parent) : QObject(parent),
                                                      statePort(8890),
                                                      telloStateAddress("0.0.0.0") {

}

TelloStateWorker::~TelloStateWorker() {
    telloStateSocketServer->close();
}

void TelloStateWorker::startStateConfig() {
    telloStateSocketServer = new QUdpSocket();

    if (!telloStateSocketServer->bind(telloStateAddress ,statePort)) {
        qInfo() << telloStateSocketServer->errorString();
        emit stateServerBindError();
    }else{
        connect(telloStateSocketServer, &QUdpSocket::readyRead, this, &TelloStateWorker::readState);
        connect(this, &TelloState::recievedNewState, this, &TelloState::stateTableConstruction);
        //csv.startDataCollect();
        connect(this, &TelloState::stateTableUpdated, &csv, &CsvHandler::collectData);
        emit stateServerStarted();
    }
}

QString TelloStateWorker::getRawState() {
    return currentRawState;
}

QHash<QString, QString> TelloStateWorker::getStateHashTable() {

}

void TelloStateWorker::readState() {
    while (telloStateSocketServer->hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloStateSocketServer->receiveDatagram();
        currentRawState = datagram.data();
        emit receivedNewStateFromTello();
    }
}

void TelloStateWorker::stateTableConstruction() {
    /*
     * How the state data looks after split(';')!
     *
     *("pitch:5", "roll:4", "yaw:0", "vgx:0", "vgy:0", "vgz:0",
     * "templ:60", "temph:61", "tof:10", "h:0", "bat:32", "baro:-8.15",
     * "time:0", "agx:99.00", "agy:-91.00", "agz:-990.00", "\r\n")
     */
    QList<QByteArray> completeTelloState = currentRawState.split(';');
    completeTelloState.removeLast(); // Remove "\r\n" from the list

    foreach(const QByteArray &stateItem, completeTelloState) {
        const QList<QByteArray> itemSeparation = stateItem.split(':');
        stateTable[itemSeparation[0]] = itemSeparation[1];
    }

    //csv.collectData(stateTable);
    emit stateTableUpdated(stateTable);
}
