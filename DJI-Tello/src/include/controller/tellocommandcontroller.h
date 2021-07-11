#ifndef TELLOCOMMANDCONTROLLER_H
#define TELLOCOMMANDCONTROLLER_H

#include <QObject>
#include <TelloEnumTypes.h>
#include <src/include/worker/tellocommandworker.h>
#include <QQueue>

Q_DECLARE_METATYPE(TelloResponse)
Q_DECLARE_METATYPE(TelloAlerts)

class TelloCommandController : public QObject {
    Q_OBJECT

public:
    explicit TelloCommandController(QObject *parent = nullptr);
    ~TelloCommandController();

private slots:
    void start();

    void processAlertSignal(TelloAlerts);
    void processResponseSignal(TelloResponse, QString);

    void defineIntentOfCommand();
    void verifyErrorMatchResponse(QString);
    void verifyOkMatchResponse(QString);
    void verifyValueMatchResponse(QString);

public slots:
    void printCommandResult(QString);
    void sendCommand(QString);

signals:
    void sendCommandToWorker(QString);

    void connectionWithTelloEstablished();
    void connectionWithTelloFailed();
    void connectionWithSocketFailed();

private:
    QThread commandWorkerThread;
    TelloCommandWorker *commandWorker;

    QString currentCommand;
    //QPair<QString, TelloResponse> commandPair;
    QQueue<QString> commandQueue;
};

#endif // TELLOCOMMANDCONTROLLER_H
