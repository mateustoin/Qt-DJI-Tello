#include "tello_connection.h"

Tello_Connection::Tello_Connection(QObject *parent) : QObject(parent), port(2020), telloPort(8889), telloAddress("192.168.10.1") {
    //moveToThread(&m_workerThread);

    //connect(&timer, &QTimer::timeout, this, &Tello_Connection::timeout);
    connect(&socket, &QUdpSocket::readyRead, this, &Tello_Connection::readyRead);

    //timer.setInterval(1000);
    //timer.moveToThread(&m_workerThread);
}

void Tello_Connection::start() {
    if (!socket.bind(port)) {
        qInfo() << socket.errorString();
        return;
    }

    qInfo() << "Started UDP on " << socket.localAddress() << ":" << socket.localPort();

    broadcast();
    //m_workerThread.start();
}

void Tello_Connection::stop() {
    timer.stop();
    socket.close();
    qInfo() << "Stopped";
}

void Tello_Connection::timeout() {
    //QString date = QDateTime::currentDateTime().toString();
    //QByteArray data = date.toLatin1();
    QByteArray data = "command";

    //QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);
    QNetworkDatagram datagram(data, telloAddress, telloPort);

    qInfo() << "Send: " << data;
    socket.writeDatagram(datagram);
}

void Tello_Connection::readyRead() {
    while (socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "Read: " << datagram.data() << " from " << datagram.senderAddress() << ":" << datagram.senderPort();
    }
}

void Tello_Connection::broadcast() {
    qInfo() << "Broadcasting info...";
    //timer.start();
    timeout();
}
