#include "src/include/controller/tellostatecontroller.h"

TelloStateController::TelloStateController(QObject *parent) : QObject(parent) {
    telloStateWorker = new TelloStateWorker();
    telloStateWorker->moveToThread(&stateWorkerThread);

    connect(&stateWorkerThread, &QThread::started,
            telloStateWorker, &TelloStateWorker::startStateConfig, Qt::QueuedConnection);
    connect(telloStateWorker, &TelloStateWorker::stateTableUpdated,
            this, &TelloStateController::updateStateTable, Qt::QueuedConnection);

    csv = new CsvHandler();
    csv->moveToThread(&csvThread);

    connect(telloStateWorker, &TelloStateWorker::stateTableUpdated,
            csv, &CsvHandler::collectData, Qt::QueuedConnection);
    connect(this, &TelloStateController::finishDataCollect,
            csv, &CsvHandler::finishDataCollect, Qt::QueuedConnection);
//    connect(&csvThread, &QThread::finished,
//            csv, &CsvHandler::finishDataCollect, Qt::QueuedConnection);

    start();
}

TelloStateController::~TelloStateController() {
    stateWorkerThread.quit();
    csvThread.quit();

    stateWorkerThread.wait();
    csvThread.wait();
}

void TelloStateController::start() {
    csvThread.start();
    stateWorkerThread.start();
}

QHash<QString, QString> TelloStateController::getStateHashTable() {
    return stateTable;
}

int TelloStateController::get_pitch() {
    /*
     * Drone pitch in degree
     * return int value
     */

    return stateTable["pitch"].toInt();
}

int TelloStateController::get_roll() {
    /*
     * Drone roll in degree
     * return int value
     */

    return stateTable["roll"].toInt();
}

int TelloStateController::get_yaw() {
    /*
     * Drone yaw in degree
     * return int value
     */

    return stateTable["yaw"].toInt();
}

int TelloStateController::get_speed_x() {
    /*
     * Drone speed in axis X
     * return int value
     */

    return stateTable["vgx"].toInt();
}

int TelloStateController::get_speed_y() {
    /*
     * Drone speed in axis Y
     * return int value
     */

    return stateTable["vgy"].toInt();
}

int TelloStateController::get_speed_z() {
    /*
     * Drone speed in axis Z
     * return int value
     */

    return stateTable["vgz"].toInt();
}

int TelloStateController::get_temp_low() {
    /*
     * Drone lowest temperature in celcius degree
     * return int value
     */

    return stateTable["templ"].toInt();
}

int TelloStateController::get_temp_high() {
    /*
     * Drone highest temperature in celcius degree
     * return int value
     */

    return stateTable["temph"].toInt();
}

float TelloStateController::get_temp_average() {
    /*
     * Drone average temperature in celcius degree
     * based on temp_high and temp_low
     * return int value
     */

    float averageTemperature = float((get_temp_high() + get_temp_low()))/2.0;
    return averageTemperature;
}

int TelloStateController::get_tof() {
    /*
     * Drone absolute distance to the floor, in cm
     * return int value
     */

    return stateTable["tof"].toInt();
}

int TelloStateController::get_height() {
    /*
     * Drone relative distance to where it started to fly
     * return int value
     */

    return stateTable["h"].toInt();
}

int TelloStateController::get_battery() {
    /*
     * Drone current battery percentage
     * return int value
     */

    return stateTable["bat"].toInt();
}

float TelloStateController::get_barometer() {
    /*
     * Drone barometer measurement in cm
     * return float value
     */

    return stateTable["baro"].toFloat();
}

int TelloStateController::get_flight_time() {
    /*
     * Flight time started when motors are started
     * return int value
     */

    return stateTable["time"].toInt();
}

float TelloStateController::get_acceleration_x() {
    /*
     * Drone acceleration on X Axis
     * return int value
     */

    return stateTable["agx"].toFloat();
}

float TelloStateController::get_acceleration_y() {
    /*
     * Drone acceleration on Y Axis
     * return int value
     */

    return stateTable["agy"].toFloat();
}

float TelloStateController::get_acceleration_z() {
    /*
     * Drone acceleration on Z Axis
     * return int value
     */

    return stateTable["agz"].toFloat();
}

void TelloStateController::updateStateTable(QHash<QString, QString> workerStateTable) {
    this->stateTable = workerStateTable;
}
