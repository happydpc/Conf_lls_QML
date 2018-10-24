import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4 as Controls_1_4
import QtQuick.Controls.Styles 1.4
import CustomControls 1.0
import QtGraphicalEffects 1.0
import "qrc:/qml/miscElems" as MiscElems
import "qrc:/qml/devices"

Rectangle {
    id: devPropertySerialPort
    color: "#e7e9eb"
    anchors.top: parent.top
    anchors.left: parent.left
    visible: true

    property var addDeviceDialog: Object
    property var messageShow: Object

    Component.onCompleted: {
        var componentQml = Qt.createComponent("qrc:/qml/devices/AddDeviceDialog.qml");
        addDeviceDialog = componentQml.createObject(devPropertySerialPort)
        addDeviceDialog.visible = false
        componentQml = Qt.createComponent("qrc:/qml/interfaces/MessageShow.qml");
        messageShow = componentQml.createObject(parent)
        addDeviceDialog.onResultMessage.connect(function(res) {
            messageShow.setData("Добавление устройства", res)
            messageShow.open()
        });
    }

    function setPropertyValues(keyProperty, valueProperty) {
        typeDeviceText.text = ""
        for(var i=0; i<valueProperty.length; i++) {
            typeDeviceText.text += valueProperty[i] + "\r\n"
        }
    }

    function setResultCheckDevice(devTypeName, devId, devSn, result) {
        addDeviceDialog.setResultCheckDevice(devTypeName, devId, devSn, result)
    }

    GridLayout {
        id: gridLayout
        width: parent.width / 2
        columnSpacing: 50
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        rowSpacing: 5
        rows: 2
        columns: 2

        Label {
            id: lTypeDevice
            height: typeDeviceText.height
            text: qsTr("Последовательный порт")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            height: 80
            width: 300
            color: "#ffffff"
            TextArea  {
            id: typeDeviceText
            text: qsTr("")
            readOnly: true
            anchors.fill: parent
            }
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
}
