import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    signal addNewConnection()
    signal closeProject()
    signal exitFull()

    MenuBar {
        id: menuMain
        anchors.left: parent.left
        anchors.leftMargin: 10

        Menu {
            title: qsTr("Connection")
            MenuItem {
                id: menuOpenProject
                text: qsTr("Add")
                onTriggered: {
                    addNewConnection()
                }
            }
            MenuItem {
                text: qsTr("Close projects")
                onTriggered: {
                    closeProject()
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: exitFull()
            }
        }
    }
}
