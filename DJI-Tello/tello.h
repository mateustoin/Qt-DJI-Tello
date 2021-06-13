#ifndef TELLO_H
#define TELLO_H

#include <QObject>
#include <tellocommand.h>
#include <tellostate.h>

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

};

#endif // TELLO_H
