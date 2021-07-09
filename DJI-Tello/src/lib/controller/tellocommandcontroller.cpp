#include "src/include/controller/tellocommandcontroller.h"

TelloCommandController::TelloCommandController(QObject *parent) : QObject(parent) {
    commandWorker = new TelloCommandWorker();
    commandWorker->moveToThread(&commandWorkerThread);
//    connect(commandWorker, &TelloCommandWorker::readyCommandResponse,
//            this, &TelloCommandController::printCommandResult, Qt::QueuedConnection);
    connect(this, &TelloCommandController::sendCommand,
            commandWorker, &TelloCommandWorker::send_control_command, Qt::QueuedConnection);
    connect(&commandWorkerThread, &QThread::started,
            commandWorker, &TelloCommandWorker::startCommandConfig, Qt::QueuedConnection);

    connect(commandWorker, &TelloCommandWorker::alertSignal,
            this, &TelloCommandController::processAlertSignal, Qt::QueuedConnection);
    connect(commandWorker, &TelloCommandWorker::responseSignal,
            this, &TelloCommandController::processResponseSignal, Qt::QueuedConnection);

    start();
}

TelloCommandController::~TelloCommandController() {
    commandWorkerThread.quit();
    commandWorkerThread.wait();
}

void TelloCommandController::processAlertSignal(TelloAlerts alert) {
    switch (alert) {
        case TelloAlerts::TELLO_CONNECTION_FAILED:
            qInfo() << "Conexão com tello falhou";
            emit connectionWithSocketFailed();
            break;

        case TelloAlerts::SOCKET_CONNECTION_FAILED:
            qInfo() << "Conexão de socket deu erro";
            emit connectionWithSocketFailed();
            break;

        case TelloAlerts::TELLO_CONNECTION_ESTABLISHED:
            qInfo() << "Conexão com Tello estabelecida";
            emit connectionWithTelloEstablished();
            break;
    }
}

void TelloCommandController::processResponseSignal(TelloResponse alert, QString response) {
    switch (alert) {
        case TelloResponse::ERROR:
            qInfo() << "Erro na resposta: " << response;
            break;

        case TelloResponse::OK:
            qInfo() << "Okay na resposta: " << response;
            emit connectionWithTelloEstablished();
            break;

        case TelloResponse::VALUE:
            qInfo() << "Valor na resposta: " << response;
            break;
    }
}

void TelloCommandController::printCommandResult(QString result) {
    qInfo() << "Command result: " << result;
}

void TelloCommandController::start() {
    commandWorkerThread.start();
}

void TelloCommandController::sendCommandToDrone(QString command) {
    emit sendCommand(command);
}
