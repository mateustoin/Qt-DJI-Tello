#ifndef TELLO_H
#define TELLO_H

#include <QObject>
#include <tellocommand.h>
#include <tellostate.h>
#include <tellovideo.h>

class Tello : public QObject
{
    Q_OBJECT
public:
    explicit Tello(QObject *parent = nullptr);
    ~Tello();

signals:

private:
    TelloCommand *tello_command;
    TelloState *tello_state;
    TelloVideo *tello_video;

};

#endif // TELLO_H
