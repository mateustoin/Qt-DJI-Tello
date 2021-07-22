#include "commandprocessor.h"
#include <QDebug>

CommandProcessor::CommandProcessor(QObject *parent) : QObject(parent),
                                                      commandReady(true){
    commandTimer = new QTimer(this);

    connect(commandTimer, &QTimer::timeout,
            this, &CommandProcessor::finishProcessCommand);
}

void CommandProcessor::startCommandAction(QString command) {
    if (isReadyForNextCommand()){
        this->commandReady = false;
        processTypeOfCommand(command);
    }else{
        qInfo() << "Not ready for next command";
    }
}

bool CommandProcessor::isReadyForNextCommand() {
    return commandReady;
}

void CommandProcessor::processTypeOfCommand(QString command) {
    if (command == "takeoff"){
        takeoff();
    }
    else if (command == "land"){
        land();
    }
    else if (command == "command" || command == "streamon" || command == "streamoff"){
        fastCommand(command);
    }
    else if (command.contains("?")){
        fastCommand(command);
    }
    else{
        slowCommand(command);
    }

    emit processingCurrentCommand();
}

void CommandProcessor::finishProcessCommand() {
    commandTimer->stop();
    commandReady = true;
    qInfo() << "Ready for next command!";
    emit readyForNextCommand();
}

void CommandProcessor::setCommand(QString command) {
    /*
     * set commands includes:
     * speed
     */
    emit startCommand(command);
    commandTimer->start(T_AVERAGE_SPEED); // Wait 1 second to process
}

void CommandProcessor::fastCommand(QString command) {
    /*
     * Common commands includes:
     * command, streamon, streamoff
     * all read commands (battery?, speed?, time?, height?, temp?, etc)
     */
    emit startCommand(command);
    commandTimer->start(T_AVERAGE_SPEED); // Wait 1 second to process
}

void CommandProcessor::slowCommand(QString command) {
    /*
     * Slow commands includes:
     * up/down/left/right, forward/back, flip
     */
    emit startCommand(command);
    commandTimer->start(T_FAST_SPEED); // Wait 0.5 second to process
}

void CommandProcessor::takeoff() {
    emit startCommand("takeoff");
    commandTimer->start(T_SLOW_SPEED); // Wait 10 seconds to process takeoff
}

void CommandProcessor::land() {
    emit startCommand("land");
    commandTimer->start(T_SLOW_SPEED); // Wait 10 seconds to process land
}
