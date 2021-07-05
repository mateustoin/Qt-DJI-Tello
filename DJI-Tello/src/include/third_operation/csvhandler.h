#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

class CsvHandler : public QObject {
    Q_OBJECT
public:
    explicit CsvHandler(QObject *parent = nullptr);

public slots:
    void startDataCollect();
    void collectData(QHash<QString,QString> stateData);
    void finishDataCollect();

private:
    QtCSV::StringData csvStateData;
    QStringList currentDataCollection;

signals:

};

#endif // CSVHANDLER_H
