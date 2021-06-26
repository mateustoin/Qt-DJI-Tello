import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tello Drone Control")

    SwipeView{
        id: swipeView
        currentIndex: navigationBar.currentIndex
        anchors.fill: parent

        ControlPage {
            id: controlPage
        }

        StatePage {
            id: statePage
        }
    }

    footer: NavigationFoot {
                id: navigationBar
                currentIndex: swipeView.currentIndex
            }
}
