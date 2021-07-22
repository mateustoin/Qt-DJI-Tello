#ifndef TELLOSTATECONTROLLER_H
#define TELLOSTATECONTROLLER_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <src/include/third_operation/csvhandler.h>
#include <src/include/worker/tellostateworker.h>

class TelloStateController : public QObject {
    Q_OBJECT
public:
    explicit TelloStateController(QObject *parent = nullptr);

public slots:
    void start();
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

private:
    QThread *csvThread;
    CsvHandler *csv;

    QThread stateWorkerThread;
    TelloStateWorker *telloStateWorker;
};

#endif // TELLOSTATECONTROLLER_H
