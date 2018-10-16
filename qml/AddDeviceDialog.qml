import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Popup {
    id: addDeviceDialog
    modal: true
    width: 600
    height: 500
    clip: true

    signal resultMessage(var res)

    function setListAvailableDevices(list) {
        console.log("AddDevice: " + list);
        typeDeviceList.model.clear()
        for(var i=0; i<list.length; i++) {
            typeDeviceList.model.append({text: list[i]})
        }
        typeDeviceList.currentIndex = 0
    }

    function setResultCheckDevice(devTypeName, result) {
        if(result === true) {
            var paramList = []
            var keyList = []
            switch(typeDeviceList.currentIndex) {
            case 0:
                if(typeDeviceList.currentText.length != 0) {
                    keyList.push("uniqDevName")
                    paramList.push(typeDeviceIdProgressTmk24.text)
                    keyList.push("password")
                    paramList.push(passwordProgressTmk24.text)
                    viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                    close()
                }
                break;
            case 1:
                break;
            }
        } else {
            resultMessage("Не удалось добавить устройство\nТак как оно не ответило на запрос")
        }
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
        Label {
            id: lTypeDevice
            x: 26
            y: 39
            text: qsTr("Тип устройства")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
        ComboBox {
            id: typeDeviceList
            anchors.right: parent.right
            anchors.rightMargin: 20
            x: 146
            y: 27
            width: 400
            height: 40
            model: ListModel {
                id: modeltypeDeviceList
            }
            onCurrentIndexChanged: {
                paramStack.setCurrentIndex(currentIndex)
            }
        }
        SwipeView {
            id: paramStack
            currentIndex: 0
            anchors.topMargin: 80
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            clip: true
            Item {
                Column {
                    id: itemProgressTMK24
                    anchors.fill: parent
                    spacing: 20
                    Row{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        spacing: 10
                        Label {
                            id: lTypeDeviceIdProgressTmk24
                            text: qsTr("ID")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField {
                            id: typeDeviceIdProgressTmk24
                            width: 250
                            height: 40
                            validator: IntValidator{bottom: 1; top: 255;}
                            placeholderText: "введите ID  адрес"
                            text: "1"
                            onFocusChanged: {
                                if(typeDeviceIdProgressTmk24.text.length === 0) {
                                    typeDeviceIdProgressTmk24.text = "1"
                                }
                            }
                        }
                    }
                    Row{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        spacing: 10
                        Label {
                            id: lPasswordDeviceProgressTmk24
                            height: 30
                            text: qsTr("Пароль")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField {
                            id: passwordProgressTmk24
                            width: 250
                            height: 40
                            placeholderText: "введите пароль"
                            maximumLength: 8
                            echoMode: TextInput.Password
                        }
                    }
                }
            }

            Item {
                Column {
                    id: itemNozzle_v0_00
                    anchors.fill: parent
                    spacing: 20
                    Row{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        spacing: 10
                        Label {
                            id: lTypeDeviceId1
                            text: qsTr("ID")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField {
                            id: typeDeviceIdNozzle_v0_00
                            width: 250
                            height: 40
                            placeholderText: "введите id номер"
                            validator: IntValidator{bottom: 1; top: 255;}
                            text: "1"
                            onFocusChanged: {
                                if(typeDeviceIdNozzle_v0_00.text.length === 0) {
                                    typeDeviceIdNozzle_v0_00.text = "1"
                                }
                            }
                        }
                    }
                    Row{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        spacing: 10
                        Label {
                            height: 30
                            text: qsTr("Пароль")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField {
                            id: passwordNozzle_v0_00
                            width: 250
                            height: 40
                            placeholderText: "введите пароль"
                            maximumLength: 8
                            echoMode: TextInput.Password
                        }
                    }
                }
            }
        }
        ButtonRound {
            id: buttonClose
            anchors.top: paramStack.bottom
            anchors.right: parent.right
            anchors.rightMargin: 10
            textLine: 2
            textIsCenter: true
            widthBody: 185
            useIcon: true
            iconCode: "\uf00d  "
            name: qsTr("Закрыть")
            y: 128
            anchors.leftMargin: 153
            onClicked: {
                close()
            }
        }

        ButtonRound {
            id: addDevButton
            anchors.top: paramStack.bottom
            anchors.right: buttonClose.left
            anchors.rightMargin: 10
            textLine: 2
            widthBody: 185
            textIsCenter: true
            name: qsTr("Добавить")
            x: -38
            y: 128
            useIcon: true
            iconCode: "\uF0FE  "
            onClicked: {
                var paramList = []
                var keyList = []
                switch(typeDeviceList.currentIndex) {
                case 0:
                    keyList.push("uniqIdDevice")
                    paramList.push(typeDeviceIdProgressTmk24.text)
                    keyList.push("password")
                    paramList.push(passwordProgressTmk24.text)
                    viewController.checkDeviceFromConnection(typeDeviceList.currentText, keyList, paramList)
                    close()
                    break;
                case 1:
                    keyList.push("uniqDevName")
                    paramList.push(typeDeviceIdNozzle_v0_00.text)
                    keyList.push("password")
                    paramList.push(passwordNozzle_v0_00.text)
                    viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                    close()
                    break;
                }
            }
        }
    }
}
