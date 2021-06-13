import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column{
        anchors.fill: parent
        Rectangle {
            color: "black"
            width: parent.width
            height: parent.height/2

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log("Start bind")
                    Tello.start()
                }
            }
        }

        Rectangle {
            color: "green"
            width: parent.width
            height: parent.height/2

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log("Send command")
                    Tello.timeout()
                }
            }
        }
    }
}
