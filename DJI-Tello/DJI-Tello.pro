QT += quick network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/lib/third_operation/csvhandler.cpp \
        src/lib/third_operation/framedecoder.cpp \
        tello.cpp \
        tellocommand.cpp \
        src/lib/controller/tellocommandcontroller.cpp \
        src/lib/worker/tellocommandworker.cpp \
        tellostate.cpp \
        src/lib/controller/tellostatecontroller.cpp \
        src/lib/worker/tellostateworker.cpp \
        tellovideo.cpp \
        src/lib/controller/tellovideocontroller.cpp \
        src/lib/worker/tellovideoworker.cpp

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
include(external/qzxing/QZXing.pri)

# Including CSV Handler library
# https://github.com/iamantony/qtcsv
include(external/qtcsv/qtcsv.pri)

HEADERS += \
    TelloEnumTypes.h \
    src/include/third_operation/csvhandler.h \
    src/include/third_operation/framedecoder.h \
    tello.h \
    tellocommand.h \
    src/include/controller/tellocommandcontroller.h \
    src/include/worker/tellocommandworker.h \
    tellostate.h \
    src/include/controller/tellostatecontroller.h \
    src/include/worker/tellostateworker.h \
    tellovideo.h \
    src/include/controller/tellovideocontroller.h \
    src/include/worker/tellovideoworker.h

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
