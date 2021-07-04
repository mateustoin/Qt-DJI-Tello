#include "tello.h"

#include <QQmlEngine>

Tello* Tello::m_pThis = nullptr;

Tello::Tello(QObject *parent) : QObject(parent) {
}

Tello::~Tello() {

}

Tello *Tello::instance() {
    if (m_pThis == nullptr){ // avoid creation of new instances
        Tello::instanciateTelloWorkers();
        m_pThis = new Tello;
    }
    return m_pThis;
}

QObject *Tello::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    // C++ and QML instance they are the same instance
    return Tello::instance();
}

void Tello::instanciateTelloWorkers() {
//    tello_command = TelloCommand::instance();
//    tello_state = TelloState::instance();
//    tello_video = TelloVideo::instance();
}
