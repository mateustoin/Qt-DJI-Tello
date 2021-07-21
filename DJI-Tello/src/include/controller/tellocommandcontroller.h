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
    void sendDirectCommand(QString);        // Send direct command to worker
    void sendCommandWithProcess(QString);   // Send command using process class

signals:
    // Internal command signals used by functions
    void sendCommandToWorker(QString);
    void sendCommandWithoutReturn(QString);
    void sendProcessCommand(QString);

    // State signals used by the interface
    void connectionWithTelloEstablished();
    void connectionWithTelloFailed();
    void connectionWithSocketFailed();

    // Operational signals used by other classes
    void readyToNextCommand();

private:
    // Worker thread creation
    QThread commandWorkerThread;
    TelloCommandWorker *commandWorker;

    // Current command storage
    QString currentCommand;
    QQueue<QString> commandQueue;
    //QPair<QString, TelloResponse> commandPair;


    bool telloIsConnected;
    bool videoIsStreaming;
    bool telloIsFlying;

    // Command processor thread creation
    CommandProcessor *commandProcessor;
    QThread processorThread;
};

#endif // TELLOCOMMANDCONTROLLER_H
