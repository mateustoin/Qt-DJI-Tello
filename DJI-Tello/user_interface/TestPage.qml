import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
    Timer{
        id: commandTimer
        interval: 15000
        repeat: true

        onTriggered: Tello.send_control_command("command")
    }

    property int divisions: 5

    Column{
        focus: true

        anchors.fill: parent
        Rectangle {
            color: "blue"
            width: parent.width
            height: parent.height/divisions

            Text {
                id: connect
                text: qsTr("Connect to drone")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    if (Tello.send_control_command("command")){
                        commandTimer.running = true;
                    } else {
                        console.log("Drone not connected");
                    }
                }
            }
        }

        Rectangle {
            color: "green"
            width: parent.width
            height: parent.height/divisions

            Text {
                id: command
                text: qsTr("Connect State Server")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    TelloState.connectStateServer();
                }
            }
        }

        Rectangle {
            color: "yellow"
            width: parent.width
            height: parent.height/divisions

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Tello.send_control_command(inputName.text);
                    //TelloState.connectStateServer()
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

                    Keys.onReturnPressed: {
                        if (event.key === Qt.Key_Return) {
                            console.log("Enter pressionado")
                            Tello.send_control_command(inputName.text);
                            inputName.clear()
                        }
                    }
                }
            }
        }

        Rectangle {
            color: "gray"
            width: parent.width
            height: parent.height/divisions

            Text {
                id: state
                text: qsTr("Read state")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    TelloState.stateTester();
                }
            }
        }

        Rectangle {
            color: "pink"
            width: parent.width
            height: parent.height/divisions

            Text {
                id: video
                text: qsTr("Start Video")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log(TelloVideo.show_video());
                }
            }
        }
    }
}
