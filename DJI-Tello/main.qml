import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

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
                    Tello.connect_tello();
                }
            }
        }

        Rectangle {
            color: "green"
            width: parent.width
            height: parent.height/divisions

            Text {
                id: command
                text: qsTr("Send command: 'command'")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log(Tello.send_control_command("command"));
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
                    console.log(TelloState.getCurrentState());
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
