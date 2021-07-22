#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <QObject>
#include <QTimer>

class CommandProcessor : public QObject {
    Q_OBJECT
public:
    explicit CommandProcessor(QObject *parent = nullptr);

public slots:
    void startCommandAction(QString);
    void finishProcessCommand();

private slots:
    bool isReadyForNextCommand();
    void processTypeOfCommand(QString);

    void setCommand(QString);
    void fastCommand(QString);
    void slowCommand(QString);
    void takeoff();
    void land();

signals:
    void processingCurrentCommand();
    void readyForNextCommand();
    void startCommand(QString);

private:
    QTimer *commandTimer;
    bool commandReady;

    // Constant variables
    const unsigned int T_FAST_SPEED = 500; // 0.5 seconds
    const unsigned int T_AVERAGE_SPEED = 1000;
    const unsigned int T_SLOW_SPEED = 10000;
};

#endif // COMMANDPROCESSOR_H
