import QtQuick 2.0
import QtQuick.Controls 2.15

TabBar {
    width: parent.width

    TabButton{
        text: qsTr("Drone Control")

        //onClicked: swipeView.setCurrentIndex(0)
    }

    TabButton{
        text: qsTr("Drone Status")

        //onClicked: swipeView.setCurrentIndex(1)
    }

    TabButton{
        text: qsTr("Grid test")

        //onClicked: swipeView.setCurrentIndex(1)
    }
}
