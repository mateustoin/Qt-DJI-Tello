#include "tello.h"

Tello::Tello(QObject *parent) : QObject(parent) {
    tello_command = new TelloCommand();
    tello_state = new TelloState();
}

Tello::~Tello() {

}
