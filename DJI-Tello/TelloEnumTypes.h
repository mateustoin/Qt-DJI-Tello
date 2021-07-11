#ifndef TELLOENUMTYPES_H
#define TELLOENUMTYPES_H

enum class TelloResponse {
    OK,                 // Answear positive
    ERROR,              // Answear negative
    VALUE,              // Answear positive with value return
    ERROR_NOT_JOYSTICK, // Wait untill send next command
    ERROR_NO_VALID_IMU, // Maybe had some changes on room light
};

enum class TelloAlerts {
    TELLO_CONNECTION_ESTABLISHED,
    TELLO_CONNECTION_FAILED,
    SOCKET_CONNECTION_FAILED,

};

#endif // TELLOENUMTYPES_H
