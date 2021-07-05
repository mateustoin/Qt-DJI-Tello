#ifndef TELLOCOMMANDCONTROLLER_H
#define TELLOCOMMANDCONTROLLER_H

#include <QObject>
#include <src/include/worker/tellocommandworker.h>

class TelloCommandController : public QObject {
    Q_OBJECT
public:
    explicit TelloCommandController(QObject *parent = nullptr);

public slots:
    void printCommandResult(QString);
    void start();
    void sendCommandToDrone(QString);

signals:
    void sendCommand(QString);

private:
    QThread commandWorkerThread;
    TelloCommandWorker commandWorker;

};

#endif // TELLOCOMMANDCONTROLLER_H
