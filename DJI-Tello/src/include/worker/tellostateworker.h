#ifndef TELLOSTATEWORKER_H
#define TELLOSTATEWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class TelloStateWorker : public QObject {
    Q_OBJECT
public:
    explicit TelloStateWorker(QObject *parent = nullptr);
    ~TelloStateWorker();

public slots:
    void startStateConfig();
    void connectStateServer(); // This is becoming startStateConfig

    QString getRawState();
    QHash<QString, QString> getStateHashTable();

private slots:
    void readState();
    void stateTableConstruction();

signals:
    void stateServerStarted();
    void stateServerBindError();

    void receivedNewStateFromTello();
    void stateTableUpdated(QHash<QString, QString>);

private:
    quint16 statePort;
    QHostAddress telloStateAddress;
    QUdpSocket *telloStateSocketServer;

    QByteArray currentRawState;
    QHash <QString, QString> stateTable;
};

#endif // TELLOSTATEWORKER_H
