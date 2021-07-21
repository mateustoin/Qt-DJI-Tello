#include "src/include/controller/tellocommandcontroller.h"

TelloCommandController::TelloCommandController(QObject *parent) : QObject(parent),
                                                                  telloIsConnected(false),
                                                                  videoIsStreaming(false),
                                                                  telloIsFlying(false){
    commandWorker = new TelloCommandWorker();
    commandWorker->moveToThread(&commandWorkerThread);

    commandProcessor = new CommandProcessor();
    commandProcessor->moveToThread(&processorThread);
    connect(this, &TelloCommandController::sendCommandToWorker,
            commandWorker, &TelloCommandWorker::send_control_command, Qt::QueuedConnection);
    connect(this, &TelloCommandController::sendCommandWithoutReturn,
            commandWorker, &TelloCommandWorker::send_command_without_return, Qt::QueuedConnection);
    connect(&commandWorkerThread, &QThread::started,
            commandWorker, &TelloCommandWorker::startCommandConfig, Qt::QueuedConnection);

    connect(commandWorker, &TelloCommandWorker::alertSignal,
            this, &TelloCommandController::processAlertSignal, Qt::QueuedConnection);
    connect(commandWorker, &TelloCommandWorker::responseSignal,
            this, &TelloCommandController::processResponseSignal, Qt::QueuedConnection);

    connect(commandProcessor, &CommandProcessor::startCommand,
            this, &TelloCommandController::sendCommand, Qt::QueuedConnection);
    connect(this, &TelloCommandController::sendCommandWithProcess,
            commandProcessor, &CommandProcessor::startCommandAction, Qt::QueuedConnection);
    connect(this, &TelloCommandController::readyToNextCommand,
            commandProcessor, &CommandProcessor::finishProcessCommand, Qt::QueuedConnection);
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
            verifyErrorMatchResponse(response);
            break;

        case TelloResponse::OK:
            if (!telloIsConnected){
               connectTelloStatusConnection();
            }

            verifyOkMatchResponse(response);
            break;

        case TelloResponse::VALUE:
            verifyValueMatchResponse(response);
            break;

        case TelloResponse::UNDEFINED:
            qInfo() << "[UNDEFINED] Command sent[" << currentCommand << "]: " << response;
            break;

        case TelloResponse::ERROR_NOT_JOYSTICK:
            qInfo() << "Command sent while drone was executing other";
            break;
        case TelloResponse::TIMEOUT:
            disconnectTelloStatusConnection();
            qInfo() << "Drone not responding";
            break;
    }
}

void TelloCommandController::sendExtraCommandToSyncResponse() {
    /*
     * Sends command to sync only if the drone is already connected
     */
    if (telloIsConnected)
        emit sendCommandWithoutReturn("command");
}

void TelloCommandController::defineIntentOfCommand() {

}

void TelloCommandController::verifyTimeoutMatchResponse(QString) {
    sendExtraCommandToSyncResponse();
    qInfo() << "Timeout on command response";
}

void TelloCommandController::verifyErrorMatchResponse(QString response) {
    // MUST SEND THE COMMAND AGAIN TO GET AN 'OK' AS ANSWEAR
    qInfo() << "[Error] Command sent[" << this->currentCommand << "]: " << response;
    this->currentCommand = "";
    sendExtraCommandToSyncResponse();
}

void TelloCommandController::verifyOkMatchResponse(QString response) {
    // MUST CONFIRM THE MATCH OF ANSWEAR AND SHOW
    if (response != "ok"){
        sendExtraCommandToSyncResponse();
    }else{
        qInfo() << "[OK] Command sent[" << this->currentCommand << "]: " << response;
        this->currentCommand = "";
        emit readyToNextCommand();
    }
}

void TelloCommandController::verifyValueMatchResponse(QString response) {
    // MUST CONFIRM THE VALUE AND SHOW
    if (!response.contains("\r\n")){
        sendExtraCommandToSyncResponse();
    }else{
        qInfo() << "[VALUE] Command sent[" << this->currentCommand << "]: " << response;
        this->currentCommand = "";
    }
}

void TelloCommandController::start() {
    commandWorkerThread.start();
    processorThread.start();
}

void TelloCommandController::initialTelloConnection() {
    if (!telloIsConnected){
        emit sendCommandWithoutReturn("command");
    }else{
        connectTelloStatusConnection();
    }
}

void TelloCommandController::connectTelloStatusConnection() {
    telloIsConnected = true;
    emit connectionWithTelloEstablished();
}

void TelloCommandController::disconnectTelloStatusConnection() {
    telloIsConnected = false;
    emit connectionWithTelloFailed();
}

void TelloCommandController::sendCommand(QString command) {
    this->currentCommand = command;
    emit sendCommandWithoutReturn(command);
}

//void TelloCommandController::sendCommandWithProcess(QString command) {
//    //commandProcessor->startCommandAction(command);
//}
