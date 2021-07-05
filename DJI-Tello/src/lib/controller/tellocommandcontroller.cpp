#include "src/include/controller/tellocommandcontroller.h"

TelloCommandController::TelloCommandController(QObject *parent) : QObject(parent) {
    connect(&commandWorker, &TelloCommandWorker::readyCommandResponse,
            this, &TelloCommandController::printCommandResult, Qt::QueuedConnection);
    connect(this, &TelloCommandController::sendCommand,
            &commandWorker, &TelloCommandWorker::send_control_command, Qt::QueuedConnection);
    connect(&commandWorkerThread, &QThread::started,
            &commandWorker, &TelloCommandWorker::startCommandConfig, Qt::QueuedConnection);

    start();
}

void TelloCommandController::printCommandResult(QString result) {
    qInfo() << "Command result: " << result;
}

void TelloCommandController::start() {
    commandWorker.moveToThread(&commandWorkerThread);
    commandWorkerThread.start();
}

void TelloCommandController::sendCommandToDrone(QString command) {
    emit sendCommand(command);
}
