#include "tellostate.h"
#include <QQmlEngine>

TelloState* TelloState::m_pThis = nullptr;

TelloState::TelloState(QObject *parent) : QObject(parent),
                                          statePort(8890),
                                          telloStateAddress("0.0.0.0") {
    //connect(this, &TelloState::stateTableUpdated, &csv, &CsvHandler::collectData);
}

TelloState::~TelloState() {
    telloStateSocketServer.close();
}

void TelloState::connectStateServer() {
    if (!telloStateSocketServer.bind(telloStateAddress ,statePort)) {
        qInfo() << telloStateSocketServer.errorString();
        return;
    }else{
        connect(&telloStateSocketServer, &QUdpSocket::readyRead, this, &TelloState::readState);
        connect(this, &TelloState::recievedNewState, this, &TelloState::stateTableConstruction);
        csv.startDataCollect();
        connect(this, &TelloState::stateTableUpdated, &csv, &CsvHandler::collectData);
        emit stateServerStarted();
    }
}

void TelloState::readState() {
    while (telloStateSocketServer.hasPendingDatagrams()) {
        QNetworkDatagram datagram = telloStateSocketServer.receiveDatagram();
        currentRawState = datagram.data();
        emit recievedNewState();
    }
}

QString TelloState::getRawState() {
    return currentRawState;
}

void TelloState::finishCsvCollect() {
    csv.finishDataCollect();
}

void TelloState::stateTableConstruction() {
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

int TelloState::get_pitch() {
    /*
     * Drone pitch in degree
     * return int value
     */

    return stateTable["pitch"].toInt();
}

int TelloState::get_roll() {
    /*
     * Drone roll in degree
     * return int value
     */

    return stateTable["roll"].toInt();
}

int TelloState::get_yaw() {
    /*
     * Drone yaw in degree
     * return int value
     */

    return stateTable["yaw"].toInt();
}

int TelloState::get_speed_x() {
    /*
     * Drone speed in axis X
     * return int value
     */

    return stateTable["vgx"].toInt();
}

int TelloState::get_speed_y() {
    /*
     * Drone speed in axis Y
     * return int value
     */

    return stateTable["vgy"].toInt();
}

int TelloState::get_speed_z() {
    /*
     * Drone speed in axis Z
     * return int value
     */

    return stateTable["vgz"].toInt();
}

int TelloState::get_temp_low() {
    /*
     * Drone lowest temperature in celcius degree
     * return int value
     */

    return stateTable["templ"].toInt();
}

int TelloState::get_temp_high() {
    /*
     * Drone highest temperature in celcius degree
     * return int value
     */

    return stateTable["temph"].toInt();
}

float TelloState::get_temp_average() {
    /*
     * Drone average temperature in celcius degree
     * based on temp_high and temp_low
     * return int value
     */

    float averageTemperature = float((get_temp_high() + get_temp_low()))/2.0;
    return averageTemperature;
}

int TelloState::get_tof() {
    /*
     * Drone absolute distance to the floor, in cm
     * return int value
     */

    return stateTable["tof"].toInt();
}

int TelloState::get_height() {
    /*
     * Drone relative distance to where it started to fly
     * return int value
     */

    return stateTable["h"].toInt();
}

int TelloState::get_battery() {
    /*
     * Drone current battery percentage
     * return int value
     */

    return stateTable["bat"].toInt();
}

float TelloState::get_barometer() {
    /*
     * Drone barometer measurement in cm
     * return float value
     */

    return stateTable["baro"].toFloat();
}

int TelloState::get_flight_time() {
    /*
     * Flight time started when motors are started
     * return int value
     */

    return stateTable["time"].toInt();
}

float TelloState::get_acceleration_x() {
    /*
     * Drone acceleration on X Axis
     * return int value
     */

    return stateTable["agx"].toFloat();
}

float TelloState::get_acceleration_y() {
    /*
     * Drone acceleration on Y Axis
     * return int value
     */

    return stateTable["agy"].toFloat();
}

float TelloState::get_acceleration_z() {
    /*
     * Drone acceleration on Z Axis
     * return int value
     */

    return stateTable["agz"].toFloat();
}

void TelloState::stateTester() {
    qInfo() << "Pitch: " << get_pitch()
            << " Roll: " << get_roll() <<
               " Yaw: " << get_yaw() <<
               " Speed x: " << get_speed_x() <<
               " Speed y: " << get_speed_y() <<
               " Speed z: " << get_speed_z() <<
               " templ: " << get_temp_low() <<
               " temph: " << get_temp_high() <<
               " tof: " << get_tof() <<
               " height" << get_height() <<
               " battery: " << get_battery() <<
               " Barometer: " << get_barometer() <<
               " Flight Time: " << get_flight_time() <<
               " AccX: " << get_acceleration_x() <<
               " AccY: " << get_acceleration_y() <<
               " AccZ" << get_acceleration_z();
}

TelloState *TelloState::instance() {
    if (m_pThis == nullptr) // avoid creation of new instances
        m_pThis = new TelloState;
    return m_pThis;
}

QObject *TelloState::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    // C++ and QML instance they are the same instance
    return TelloState::instance();
}
