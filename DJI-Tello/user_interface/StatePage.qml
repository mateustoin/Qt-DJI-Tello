import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {

    GridLayout {
        id: mainLayout1
        anchors.fill: parent
        focus: true

        rows: 3
        columns: 3

        property double colWidth: width/columns
        property double rowHeight: height/rows

        Connections{
            target: TelloState

            function onStateTableUpdated() {
                var battery = TelloState.get_battery();
                var temperature = TelloState.get_temp_average();
                var tof = TelloState.get_tof();
                var pitch = TelloState.get_pitch();
                var roll = TelloState.get_roll();
                var yaw = TelloState.get_yaw();
                var accx = TelloState.get_acceleration_x();
                var accy = TelloState.get_acceleration_y();
                var accz = TelloState.get_acceleration_z();
                batteryText.text = "Battery: \n" + battery.toString() + "%";
                temperatureText.text = "Temperature: \n" + temperature.toString() + "ºC";
                tofText.text = "TOF: \n" + tof.toString() + "cm";
                pitchText.text = "Pitch: \n" + pitch.toString() + "º";
                rollText.text = "Roll: \n" + roll.toString() + "º";
                yawText.text = "Yaw: \n" + yaw.toString() + "º";
                accXText.text = "Acceleration X: \n" + accx.toString();
                accYText.text = "Acceleration Y: \n" + accy.toString();
                accZText.text = "Acceleration Z: \n" + accz.toString();
            }
        }

        function prefWidth(item){
            return ((colWidth * item.Layout.columnSpan) + (columnSpacing * (item.Layout.columnSpan-1)))
        }
        function prefHeight(item){
            return ((rowHeight * item.Layout.rowSpan) + (rowSpacing * (item.Layout.rowSpan -1)))
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: batteryText
                anchors.centerIn: parent
                text: "Battery: \n0%"
            }
        }

        Rectangle {
            color: "white"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: temperatureText
                anchors.centerIn: parent
                text: "Temperature: \n0ºC"
            }
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: tofText
                anchors.centerIn: parent
                text: "TOF: \n0cm"
            }
        }

        Rectangle {
            color: "white"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: pitchText
                anchors.centerIn: parent
                text: "Pitch: \n0º"
            }
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: rollText
                anchors.centerIn: parent
                text: "Roll: \n0º"
            }
        }

        Rectangle {
            color: "white"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: yawText
                anchors.centerIn: parent
                text: "Yaw: \n0º"
            }
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: accXText
                anchors.centerIn: parent
                text: "Acc X: \n0"
            }
        }

        Rectangle {
            color: "white"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: accYText
                anchors.centerIn: parent
                text: "Acc Y: \n0"
            }
        }

        Rectangle {
            color: "pink"
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.preferredWidth: mainLayout1.prefWidth(this)
            Layout.preferredHeight: mainLayout1.prefHeight(this)
            property int batteryValue: 0

            Text {
                id: accZText
                anchors.centerIn: parent
                text: "Acc Z: \n0"
            }
        }
    }
}
