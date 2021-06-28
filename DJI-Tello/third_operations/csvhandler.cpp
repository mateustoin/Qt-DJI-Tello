#include "csvhandler.h"

CsvHandler::CsvHandler(QObject *parent) : QObject(parent) {
    startDataCollect();
}

void CsvHandler::startDataCollect() {
    csvStateData.clear();
    currentDataCollection.clear();

    currentDataCollection << "pitch" << "roll" << "yaw"
                          << "vgx" << "vgy" << "vgz"
                          << "temperature_low" << "temperature_high" << "tof"
                          << "height" << "battery" << "barometer"
                          << "time" << "acc_x" << "acc_y" << "acc_z";
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void CsvHandler::collectData(QHash<QString, QString> stateData) {
    currentDataCollection << stateData["pitch"] << stateData["roll"] << stateData["yaw"]
                          << stateData["vgx"] << stateData["vgy"] << stateData["vgz"]
                          << stateData["templ"] << stateData["temph"] << stateData["tof"]
                          << stateData["h"] << stateData["bat"] << stateData["baro"]
                          << stateData["time"] << stateData["agx"] << stateData["agy"] << stateData["agz"];
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void CsvHandler::finishDataCollect() {
    qInfo() << "Saving data to: " << QDir::currentPath();
    QDateTime fileCreationDateTime;
    QString nameComplement = fileCreationDateTime.currentDateTime().toString("h:m:s ap");
    QString filePath = QDir::currentPath() + "/tello-data-" + nameComplement + ".csv";
    QtCSV::Writer::write(filePath, csvStateData);

    csvStateData.clear();
}
