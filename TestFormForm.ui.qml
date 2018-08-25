import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Rectangle {
    id: devPropertySerialPort
    color: "#e7e9eb"
    property alias addDevButton: addDevButton

    width: 800
    height: 500


    //    anchors.fill: parent

    //    function setInformation(arg) {

    //    }
    GridLayout {
        id: gridLayout
        width: 384
        anchors.bottomMargin: 305
        columnSpacing: 5
        anchors.right: tabBar.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
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
            font.underline: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: lTypeDevice.left
            anchors.leftMargin: 150
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
            width: 100
            height: 100
            text: qsTr("...")
            Layout.fillHeight: true
            font.underline: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: lSn.left
            anchors.leftMargin: 150
            readOnly: true
        }
        Button {
            id: addDevButton
            x: -402
            y: 174
            width: 250
            text: qsTr("Добавить устройство")
            //            onClicked: {

            //            }
        }
    }
}
