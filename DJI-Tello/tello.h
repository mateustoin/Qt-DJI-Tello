#ifndef TELLO_H
#define TELLO_H

#include <QObject>
#include <tellocommand.h>
#include <tellostate.h>
#include <tellovideo.h>
#include <QThread>

class QQmlEngine;
class QJSEngine;

class Tello : public QObject {
    Q_OBJECT
public:
    explicit Tello(QObject *parent = nullptr);
    ~Tello();
    static Tello *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    TelloCommand *tello_command;
    TelloState *tello_state;
    TelloVideo *tello_video;

public slots:

private slots:
    static void instanciateTelloWorkers();

signals:

private:
    static Tello* m_pThis;

    QThread threadTelloCommand;
    QThread threadTelloState;
    QThread threadTelloVideo;
};

#endif // TELLO_H
