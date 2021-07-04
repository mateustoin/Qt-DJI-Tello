#ifndef TELLOSTATE_H
#define TELLOSTATE_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHash>

#include <third_operations/csvhandler.h>

class QQmlEngine;
class QJSEngine;

class TelloState : public QObject {
    Q_OBJECT
public:
    static TelloState *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    ~TelloState();

public slots:
    void connectStateServer();
    QString getRawState();
    void finishCsvCollect();

    int get_pitch();
    int get_roll();
    int get_yaw();
    int get_speed_x();
    int get_speed_y();
    int get_speed_z();
    int get_temp_low();
    int get_temp_high();
    float get_temp_average();
    int get_tof();
    int get_height();
    int get_battery();
    float get_barometer();
    int get_flight_time();
    float get_acceleration_x();
    float get_acceleration_y();
    float get_acceleration_z();
    void stateTester();

signals:
    void stateServerStarted();
    void recievedNewState();
    void stateTableUpdated(QHash<QString, QString>);

private slots:
    void readState();
    void stateTableConstruction();

private:
    explicit TelloState(QObject *parent = nullptr);
    static TelloState* m_pThis;

    quint16 statePort;
    QHostAddress telloStateAddress;
    QUdpSocket telloStateSocketServer;

    QByteArray currentRawState;
    QHash <QString, QString> stateTable;

    CsvHandler csv;
};

#endif // TELLOSTATE_H
