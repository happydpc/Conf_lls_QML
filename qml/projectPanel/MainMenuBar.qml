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
            title: qsTr("Соединение")
            MenuItem {
                id: menuOpenProject
                text: qsTr("Добавить")
                onTriggered: {
                    addNewConnection()
                }
            }
            MenuItem {
                text: qsTr("Закрыть")
                onTriggered: exitFull()
            }
        }
    }
}
