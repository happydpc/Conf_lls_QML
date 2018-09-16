import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2

Rectangle {
    id: devicePanel
    anchors.fill: parent

    signal addNewConnection()

    property alias  devicePropertyPanel: devicePropertyPanel

    Rectangle {
        id: interfaceTree
        width: 220
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        height: parent.height / 2
        color: "transparent"
        ListView {
            id: listInterfaceView
            anchors.fill: interfaceTree
            spacing: 20
            clip: true
            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }
            model: programmModel.tree
            delegate: InterfaceItemView {
                onEventClickLeft: {
                    console.log("event left click")
                }
                onEventClickRight: {
                    console.log("event right click")
                    removeInterfaceDialog.open()
                }
                Dialog {
                    id:removeInterfaceDialog
                    visible: false
                    title: "Удалить интерфейс"
                    standardButtons: StandardButton.Close | StandardButton.Apply
                    Rectangle {
                        color: "transparent"
                        implicitWidth: 250
                        implicitHeight: 100
                        Text {
                            text: "Вы хотите удалить интерфейс?"
                            color: "black"
                            anchors.centerIn: parent
                        }
                    }
                    onApply: {
                        viewController.removeActiveInterface()
                        close()
                    }
                }
            }
        }
    }

    Rectangle {
        id:spacerList
        anchors.top: interfaceTree.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right
        width: interfaceTree.width
        height: 2
        color: "#f0f3f6"
    }
    Rectangle {
        id:spacerListVectical
        anchors.top: interfaceTree.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.right: interfaceTree.right
        width: 2
        height: parent.height
        color: "#f0f3f6"
    }

    Button {
        id:addInterfaceButton
        anchors.top: spacerList.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right
        width: interfaceTree.width
        height: 50
        background: Rectangle {
            height: 50
            width: widthBody
            radius: 25
            color: addInterfaceButton.pressed ? "#a3ff7b" : "#ffffff"
            border.color: "#e9eff4"
            border.width: 2
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: 16
                anchors.top: parent.top
                anchors.topMargin: 17
                color: "#3598fa"
                width: 16
                height: 16
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 17
                anchors.leftMargin: 40
                font.pointSize: 8
                color: addInterfaceButton.pressed ? "black" : "#3598fa"
                text: qsTr("Добавить интерфейс")
            }
        }
        onClicked: {
            addNewConnection();
        }
    }
    Button {
        id:settingsButton
        anchors.top: addInterfaceButton.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right
        width: interfaceTree.width
        height: 50
        enabled: false
        background: Rectangle {
            height: 50
            width: widthBody
            radius: 25
            color: settingsButton.pressed ? "#a3ff7b" : "#ffffff"
            border.color: "#e9eff4"
            border.width: 2
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: 16
                anchors.top: parent.top
                anchors.topMargin: 17
                color: "#3598fa"
                width: 16
                height: 16
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 17
                anchors.leftMargin: 40
                font.pointSize: 8
                color: settingsButton.pressed ? "black" : "#3598fa"
                text: qsTr("Настройки")
            }
        }
    }
    Button {
        id:supportButton
        anchors.top: settingsButton.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right
        width: interfaceTree.width
        height: 50
        enabled: false
        background: Rectangle {
            height: 50
            width: widthBody
            radius: 25
            color: supportButton.pressed ? "#a3ff7b" : "#ffffff"
            border.color: "#e9eff4"
            border.width: 2
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: 16
                anchors.top: parent.top
                anchors.topMargin: 17
                color: "#3598fa"
                width: 16
                height: 16
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 17
                anchors.leftMargin: 40
                font.pointSize: 8
                color: supportButton.pressed ? "black" : "#3598fa"
                text: qsTr("Поддержка")
            }
        }
    }

    DevicePropertyPanel {
        id: devicePropertyPanel
        visible: true
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: interfaceTree.right
        anchors.right: parent.right
    }
}
