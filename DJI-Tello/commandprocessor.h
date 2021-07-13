#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <QObject>
#include <QTimer>

class CommandProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcessor(QObject *parent = nullptr);

public slots:
    void startCommandAction(QString);

private slots:
    bool isReadyForNextCommand();
    void processTypeOfCommand(QString);

    void finishProcessCommand();

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
};

#endif // COMMANDPROCESSOR_H
