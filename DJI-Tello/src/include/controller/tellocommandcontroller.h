#ifndef TELLOCOMMANDCONTROLLER_H
#define TELLOCOMMANDCONTROLLER_H

#include <QObject>
#include <TelloEnumTypes.h>
#include <src/include/worker/tellocommandworker.h>

Q_DECLARE_METATYPE(TelloResponse)
Q_DECLARE_METATYPE(TelloAlerts)

class TelloCommandController : public QObject {
    Q_OBJECT

public:
    explicit TelloCommandController(QObject *parent = nullptr);
    ~TelloCommandController();

private slots:
    void processAlertSignal(TelloAlerts);
    void processResponseSignal(TelloResponse, QString);

public slots:
    void printCommandResult(QString);
    void start();
    void sendCommandToDrone(QString);

signals:
    void sendCommand(QString);

    void connectionWithTelloEstablished();
    void connectionWithTelloFailed();
    void connectionWithSocketFailed();

private:
    QThread commandWorkerThread;
    TelloCommandWorker *commandWorker;
};

#endif // TELLOCOMMANDCONTROLLER_H
