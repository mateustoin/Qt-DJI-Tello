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
            color: "blue"
            width: parent.width
            height: parent.height/4

            Text {
                id: connect
                text: qsTr("Connect to drone")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Tello.connect_tello();
                }
            }
        }

        Rectangle {
            color: "green"
            width: parent.width
            height: parent.height/4

            Text {
                id: command
                text: qsTr("Send command: 'command'")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Tello.send_control_command("command");
                }
            }
        }

        Rectangle {
            color: "yellow"
            width: parent.width
            height: parent.height/4

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    //Tello.send_control_command(inputName.text);
                    TelloState.connectStateServer()
                }
            }

            Rectangle{
                id: inputNameBox
                color: "white"

                width: 100
                height: 40
                anchors.centerIn: parent

                TextInput {
                    id: inputName

                    width: parent.width
                    height: parent.height*0.8
                    anchors.verticalCenter: parent.verticalCenter
                    cursorVisible: false
                    maximumLength: 15
                }
            }
        }

        Rectangle {
            color: "gray"
            width: parent.width
            height: parent.height/4

            Text {
                id: state
                text: qsTr("Read state")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log(TelloState.getCurrentState());
                }
            }
        }
    }
}
