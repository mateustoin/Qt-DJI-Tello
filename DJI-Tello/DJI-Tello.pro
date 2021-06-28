QT += quick network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        third_operations/csvhandler.cpp \
        third_operations/framedecoder.cpp \
        main.cpp \
        tello.cpp \
        tellocommand.cpp \
        tellostate.cpp \
        tellovideo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Including QrCode libraries
include(qzxing/QZXing.pri)

# Including CSV Handler library
# https://github.com/iamantony/qtcsv
include(qtcsv/qtcsv.pri)

HEADERS += \
    third_operations/csvhandler.h \
    third_operations/framedecoder.h \
    tello.h \
    tellocommand.h \
    tellostate.h \
    tellovideo.h

win32: {
    include("c:/dev/opencv/opencv.pri")
}

unix: !macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

unix: macx {
    INCLUDEPATH += "/usr/local/include"
    LIBS += -L"/usr/local/lib" \
    -lopencv_world
}
