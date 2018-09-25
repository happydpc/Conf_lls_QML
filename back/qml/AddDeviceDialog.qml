import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Popup {
    id: addDeviceDialog
    modal: true
    y: width / 2
    x: height / 2
    width: 400
    height: 250

    Rectangle {
        anchors.fill: parent

        GridLayout {
            id: gridLayout
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height - buttonClose.height - 5
            columnSpacing: 10
            rowSpacing: 0
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
        }

        ButtonRound {
            id: buttonClose
            anchors.top: gridLayout.bottom
            anchors.left: parent.left
            anchors.rightMargin: 10
            textLine:2
            textIsCenter: true
            widthBody: 185
            name: qsTr("Закрыть")
            onClicked: {
                close()
            }
        }
        ButtonRound {
            id: addDevButton
            textLine:2
            widthBody: 185
            textIsCenter: true
            name: qsTr("Добавить")
            anchors.top: gridLayout.bottom
            anchors.right: parent.right
            onClicked: {
                if (typeDeviceText.currentText.length != 0) {
                    viewController.addDeviceToConnection(typeDeviceText.currentText, typeDeviceIdText.value.toString(), passwordText.text)
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
