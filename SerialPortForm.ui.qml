import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3

Popup {
    id: popup
    width: 330
    height: 220
    property alias buttonUpdate: buttonUpdate
    property alias buttonAccept: buttonAccept
    property alias buttonClose: buttonClose
    property alias portList: portList
    property alias baudRateList: baudRateList
    dim: false
    clip: false

    modal: true

    Row {
        id: row_2
        height: 43
        anchors.top: row_1.bottom
        anchors.topMargin: 10
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
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }

    Row {
        id: row_3
        y: 122
        height: 67
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: row_2.top
        anchors.bottomMargin: -120

        Button {
            id: buttonAccept
            width: 140
            height: 66
            text: qsTr("Accept")
            anchors.left: parent.left
            anchors.leftMargin: 0
        }
        Button {
            id: buttonClose
            width: 140
            height: 66
            text: qsTr("Close")
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
    }

    Row {
        id: row_1
        x: 10
        y: 10
        height: 46
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        ComboBox {
            id: portList
            editable: true
            model: ListModel {
                id: modelPortList
            }
            anchors.left: parent.left
            anchors.leftMargin: 0
        }
        Button {
            id: buttonUpdate
            width: 128
            height: 40
            text: qsTr("Update")
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
    }
}
