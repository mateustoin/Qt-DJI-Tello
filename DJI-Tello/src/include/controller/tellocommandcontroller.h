#ifndef TELLOCOMMANDCONTROLLER_H
#define TELLOCOMMANDCONTROLLER_H

#include <QObject>
#include <TelloEnumTypes.h>
#include <src/include/worker/tellocommandworker.h>
#include <QQueue>
#include <QTimer>
#include <commandprocessor.h>

Q_DECLARE_METATYPE(TelloResponse)
Q_DECLARE_METATYPE(TelloAlerts)

class TelloCommandController : public QObject {
    Q_OBJECT

public:
    explicit TelloCommandController(QObject *parent = nullptr);
    ~TelloCommandController();

private slots:
    void start();
    void initialTelloConnection();
    void connectTelloStatusConnection();
    void disconnectTelloStatusConnection();

    void processAlertSignal(TelloAlerts);
    void processResponseSignal(TelloResponse, QString);

    void sendExtraCommandToSyncResponse();
    void defineIntentOfCommand();
    void verifyTimeoutMatchResponse(QString);
    void verifyErrorMatchResponse(QString);
    void verifyOkMatchResponse(QString);
    void verifyValueMatchResponse(QString);

public slots:
    void sendCommand(QString);

signals:
    void sendCommandToWorker(QString);
    void sendCommandWithoutReturn(QString);
    void sendCommandWithProcess(QString);

    void connectionWithTelloEstablished();
    void connectionWithTelloFailed();
    void connectionWithSocketFailed();

private:
    QThread commandWorkerThread;
    TelloCommandWorker *commandWorker;

    QString currentCommand;
    QQueue<QString> commandQueue;
    //QPair<QString, TelloResponse> commandPair;

    bool telloIsConnected;
    bool videoIsStreaming;
    bool telloIsFlying;

    CommandProcessor *commandProcessor;
    QThread processorThread;
};

#endif // TELLOCOMMANDCONTROLLER_H
