import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Popup {
    id: addDeviceDialog

    dim: false
    clip: false

    modal: true

    y: width / 2
    x: height / 2
    width: 400
    height: 250
    font.capitalization: Font.AllUppercase

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columnSpacing: 5
        rowSpacing: 5
        rows: 4
        columns: 2

        Label {
            id: lTypeDevice
            text: qsTr("Тип устройства")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        ComboBox {
            id: typeDeviceText
            Layout.fillWidth: true
            model: ListModel {
                id: modelTypeDeviceText
            }
        }

        Label {
            id: lTypeDeviceId
            text: qsTr("ID")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        SpinBox {
            id: typeDeviceIdText
            Layout.fillWidth: true
            from: 1
            to: 255
            value: 1
        }

        Label {
            id: lPassword
            height: typeDeviceIdText.height
            text: qsTr("Пароль")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: passwordText
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: typeDeviceText.left
            maximumLength: 8
            echoMode: TextInput.Password
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
            Layout.fillWidth: true
            onClicked: {
                if (typeDeviceText.currentText.length != 0) {
                    viewController.addDeviceToConnection(typeDeviceText.currentText, typeDeviceIdText.value.toString(), passwordText.text)
                    close()
                }
            }
        }
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            horizontalOffset: 0
            verticalOffset: 1
            color: "#e0e5ef"
            samples: 10
            radius: 20
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
