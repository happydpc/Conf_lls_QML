import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Rectangle {
    id: devPropertySerialPort
    color: "#e7e9eb"
    anchors.fill: parent

    function setPropertyValues(listData) {
        typeDeviceText.text = listData[3]
        information.text = listData[0] + "\r\n" + listData[1]
                + "\r\n" + listData[2] + "\r\n" + listData[4]
    }

    GridLayout {
        id: gridLayout
        width: parent.width
        columnSpacing: 5
        anchors.right: tabBar.left
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
            text: qsTr("Порт")
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
    }

    Button {
        id: addDevButton
        x: 271
        width: 230
        text: qsTr("Добавить устройство")
        anchors.right: gridLayout.right
        anchors.rightMargin: 0
        anchors.top: gridLayout.bottom
        anchors.topMargin: 20
        onClicked: {
            var list = viewController.getAvailableDeviceNameToSerialPort()
            console.log("addDeviceToSerialPort-" + list)
            addDeviceDialog.setListAvailableDevices(list)
            addDeviceDialog.open()
        }
    }

    AddDeviceDialog {
        id:addDeviceDialog
    visible: false
    }
}
