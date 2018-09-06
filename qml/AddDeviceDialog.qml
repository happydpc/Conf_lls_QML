import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Popup {
    id: addDeviceDialog

    dim: false
    clip: false

    modal: true

    y: width / 2
    x: height / 2
    width: 400
    height: 150
    font.capitalization: Font.AllUppercase

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columnSpacing: 5
        anchors.right: tabBar.left
        rowSpacing: 5
        rows: 3
        columns: 2

        Label {
            id: lTypeDevice
            height: typeDeviceText.height
            text: qsTr("Тип устройства")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ComboBox {
            id: typeDeviceText
            font.underline: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: lTypeDevice.left
            anchors.leftMargin: 150
            model: ListModel {
                id: modelTypeDeviceText
            }
        }

        Label {
            id: lTypeDeviceId
            height: typeDeviceIdText.height
            text: qsTr("ID")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        SpinBox {
            id: typeDeviceIdText
            font.underline: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: typeDeviceText.left
        }

        Button {
            id: buttonClose
            text: qsTr("Закрыть")
            Layout.fillWidth: true
            onClicked: {
                close()
            }
        }

        Button {
            id: addDevButton
            text: qsTr("Добавить")
            onClicked: {
                if (typeDeviceText.currentText.length != 0) {
                    viewController.addDeviceToConnection(typeDeviceText.currentText, typeDeviceIdText.value.toString())
                    close()
                }
            }
        }
    }

    function setListAvailableDevices(list) {
        console.log("AddDevice: " + list);
        typeDeviceText.model.clear()
        for(var i=0; i<list.length; i++) {
            typeDeviceText.model.append({text: list[i]})
        }
        typeDeviceText.currentIndex = 0
    }
}
