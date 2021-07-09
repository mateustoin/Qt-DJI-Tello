#ifndef TELLOENUMTYPES_H
#define TELLOENUMTYPES_H

enum class TelloResponse {
    OK,
    ERROR,
    VALUE
};

enum class TelloAlerts {
    TELLO_CONNECTION_ESTABLISHED,
    TELLO_CONNECTION_FAILED,
    SOCKET_CONNECTION_FAILED,

};

#endif // TELLOENUMTYPES_H
