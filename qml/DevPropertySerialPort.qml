import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Rectangle {
    id: devPropertySerialPort
    color: "#e7e9eb"
    anchors.fill: parent

    property alias addDeviceDialog: addDeviceDialog

    function setPropertyValues(listData) {
        typeDeviceText.text = listData[3]
        information.text = listData[0] + "\r\n" + listData[1]
                + "\r\n" + listData[2] + "\r\n" + listData[4]
    }

    GridLayout {
        id: gridLayout
        width: parent.width
        columnSpacing: 5
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        rowSpacing: 5
        rows: 3
        columns: 2

        Label {
            id: lTypeDevice
            height: typeDeviceText.height
            text: qsTr("Последовательный порт")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: typeDeviceText
            text: qsTr("")
            readOnly: true
        }

        Label {
            id: lSn
            height: information.height
            text: qsTr("Информация")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextArea {
            id: information
            width: parent.width
            height: 100
            text: qsTr("...")
            readOnly: true
        }
        Button {
            id: addDevButton
            text: qsTr("Добавить устройство")
            onClicked: {
                var list = viewController.getDeviceAvailableType()
                addDeviceDialog.setListAvailableDevices(list)
                addDeviceDialog.open()
            }
        }
    }

    AddDeviceDialog {
        id:addDeviceDialog
        visible: false
        x: window.x / 2
        y: window.y / 2
        onResultMessage: {
            dialogMessage.message = res
            dialogMessage.title = "Добавление устройства"
            dialogMessage.open()
            timerUntili.start()
        }
        Timer {
            id: timerUntili
            interval: 2000
            running: false
            repeat: false
            onTriggered: {
                dialogMessage.close()
            }
        }
    }
    Dialog {
        id: dialogMessage
        visible: false
        title: ""
        clip: true
        standardButtons: StandardButton.Apply
        property string message: ""
        Rectangle {
            color: "transparent"
            implicitWidth: 400
            implicitHeight: 200
            Text {
                text: dialogMessage.message
                color: "black"
                anchors.centerIn: parent
            }
        }
    }
}
