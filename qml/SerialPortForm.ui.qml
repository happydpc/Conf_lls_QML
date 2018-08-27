import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3

Popup {
    id: popup
    width: 450
    height: 270
    property alias buttonUpdate: buttonUpdate
    property alias buttonAccept: buttonAccept
    property alias buttonClose: buttonClose
    property alias portList: portList
    property alias baudRateList: baudRateList
    dim: false
    clip: false

    modal: true

    GroupBox {
        id: groupBoxSerialPort
        x: 9
        y: 8
        width: 382
        height: 171
        title: qsTr("SerialPort")

        Row {
            id: row_1
            x: -12
            y: -171
            height: 46
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 10

            ComboBox {
                id: portList
                editable: true
                model: ListModel {
                    id: modelPortList
                }
            }

            Button {
                id: buttonAccept
                width: 120
                height: 40
                text: qsTr("Connect")
                anchors.right: parent.right
                anchors.rightMargin: 0
            }
            Button {
                id: buttonUpdate
                width: 70
                height: 40
                text: qsTr("Update")
                enabled: false
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: portList.left
                anchors.leftMargin: 150
            }
        }

        Row {
            id: row_2
            x: -12
            y: -115
            height: 43
            anchors.top: row_1.bottom
            anchors.topMargin: 6
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10

            ComboBox {
                id: baudRateList
                editable: true
                model: ListModel {
                    id: modelBaudrateList
                }
            }

            Label {
                id: baudLabel
                text: qsTr("Baudrate")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: baudRateList.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
        }
    }

    Button {
        id: buttonClose
        x: 44
        y: 195
        width: 140
        height: 50
        text: qsTr("Close")
        anchors.right: parent.right
        anchors.rightMargin: 266
    }
}
