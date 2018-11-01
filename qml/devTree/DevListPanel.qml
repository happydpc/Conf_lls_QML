import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Controls 1.4 as ControlOld
import QtQuick.Controls.Styles 1.4
import CustomControls 1.0
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11
import "qrc:/qml/devices"
import "qrc:/qml/interfaces"
import "qrc:/qml/miscElems"
import "qrc:/qml/projectPanel"

Rectangle {
    id: devicePanel
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
                onEventSelectInterface: {}
                onEventDeleteInterface: {
                    removeInterfaceDialog.open()
                }
                Dialog {
                    id:removeInterfaceDialog
                    visible: false
                    title: "Удалить интерфейс"
                    standardButtons: StandardButton.Close | StandardButton.Ok
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
        anchors.rightMargin: 10
        width: 2
        height: parent.height
        color: "#f0f3f6"
    }
    DevicePropertyPanel {
        id: devicePropertyPanel
        visible: true
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: interfaceTree.right
        anchors.right: parent.right
    }
    Column {
        spacing: 5
        anchors.top: interfaceTree.bottom
        anchors.topMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right

        ButtonRound {
            id:sessionButton
            textLine:2
            widthBody: interfaceTree.width - 40
            name: qsTr("Сеанс")
            useIcon: true
            iconCode: "\uF0FE  "
            onClicked: {
                var componentQml = Qt.createComponent("qrc:/qml/projectPanel/Session.qml");
                var item = componentQml.createObject(devicePropertyPanel)
                item.x = devicePropertyPanel.height / 6
                item.y = devicePropertyPanel.width / 6
                item.open()
                item.onClosed.connect(function() {
                    item.destroy()
                });
            }
        }
        ButtonRound {
            id:addInterfaceButton
            textLine:2
            widthBody: interfaceTree.width - 40
            name: qsTr("Добавить интерфейс")
            useIcon: true
            iconCode: "\uF0FE  "
            onClicked: {
                addNewConnection();
            }
        }
        ButtonRound {
            id:settingsButton
            textLine:2
            widthBody: interfaceTree.width - 40
            name: qsTr("Обновление")
            useIcon: true
            iconCode: "\uF54A  "
            onClicked: {
                settings.open()
            }
        }
        ButtonRound {
            id:supportButton
            textLine:2
            widthBody: interfaceTree.width - 40
            name: qsTr("Поддержка")
            useIcon: true
            iconCode: "\uF0E0  "
            onClicked: {
                support.open()
            }
        }
    }
    Support {
        id:support
    }
    Settings {
        id:settings
    }
}
