import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15

Page {
    Timer{
        id: commandTimer
        interval: 15000
        repeat: true

        onTriggered: Tello.send_control_command("command")
    }

    Connections{
        target: Tello

        function onConnectionWithTelloEstablished(){
            connRectangle.color = "green";
            commandTimer.running = true;
        }

        function onConnectionWithTelloFailed(){
            connRectangle.color = "red";
            console.log("Drone not connected!");
        }
    }

    GridLayout {
        id: mainLayout1
        focus: true

        columnSpacing: 2
        rowSpacing: 2

        rows: 4
        columns: 6

        property double colWidth: parent.width/columns
        property double rowHeight: parent.height/rows

        function prefWidth(item){
            return ((colWidth * item.Layout.columnSpan) + (columnSpacing * (item.Layout.columnSpan-1)))
        }
        function prefHeight(item){
            return ((rowHeight * item.Layout.rowSpan) + (rowSpacing * (item.Layout.rowSpan -1)))
        }

        Timer{
            id: statusTimer
            interval: 1000
            repeat: true

            onTriggered: {
                var battery = TelloState.get_battery();
                var temperature = TelloState.get_temp_average();
                var tof = TelloState.get_tof();
                batteryText.text = "Battery: " + battery.toString();
                temperatureText.text = "Temperature: " + temperature.toString();
                tofText.text = "TOF: " + tof.toString();
            }
        }

        Rectangle {
            color: "red"
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: batteryText
                anchors.centerIn: parent
                text: "Battery: "
            }
        }

        Rectangle {
            color: "green"
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int temperatureValue: 0

            Text {
                id: temperatureText
                anchors.centerIn: parent
                text: "Temperature: "
            }
        }

        Rectangle {
            color: "gray"
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int tofValue: 0

            Text {
                id: tofText
                anchors.centerIn: parent
                text: "TOF: "
            }
        }

        Rectangle {
            id: connRectangle
            color: "blue"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

            Text {
                id: connect
                text: qsTr("Connect to drone")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Tello.connectTello()
                }
            }
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

            Text {
                id: command
                text: qsTr("Connect State Server")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    TelloState.connectStateServer();
                    //statusTimer.start();
                }
            }
        }

        Rectangle {
            color: "orange"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

            Text {
                id: streamText
                text: qsTr("Start Drone Stream")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log(Tello.send_control_command("streamon"));
                }
            }
        }

        Rectangle {
            color: "brown"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

            Text {
                id: video
                text: qsTr("Start Video")
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log(TelloVideo.startVideoStream());
                }
            }
        }

        Rectangle {
            color: "purple"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

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
            color: "white"
            Layout.columnSpan: 3
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)

            MouseArea{
                anchors.fill: parent

                onClicked: TelloState.finishCsvCollect()
            }
        }
    }
}
