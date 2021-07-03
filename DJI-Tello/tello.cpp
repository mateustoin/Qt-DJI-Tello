#include "tello.h"

Tello::Tello(QObject *parent) : QObject(parent) {
    //moveToThread(&thread);

    tello_command = new TelloCommand();
    tello_state = new TelloState();
    tello_video = new TelloVideo();
    qInfo() << "TelloCommand rodando na thread: " << tello_command->thread();
    qInfo() << "TelloVideo rodando na thread: " << tello_video->thread();
    qInfo() << "TelloState rodando na thread: " << tello_state->thread();

    tello_video->moveToThread(&thread);
    qInfo() << "TelloVideo rodando na thread: " << tello_video->thread();
}

Tello::~Tello() {

}

void Tello::show_video()
{
    tello_video->startVideoStream();
}
