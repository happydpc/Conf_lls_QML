import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Popup {
    id: addDeviceDialog
    modal: true
    y: width / 2
    x: height / 2
    width: 600
    height: 500

    Rectangle {
        id: rectangle
        anchors.rightMargin: 250
        anchors.bottomMargin: 300
        anchors.leftMargin: -250
        anchors.topMargin: -300
        anchors.fill: parent

        Label {
            id: lTypeDevice
            x: 26
            y: 39
            text: qsTr("Тип устройства")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        ComboBox {
            id: typeDeviceText
            x: 146
            y: 27
            width: 446
            height: 40
            Layout.fillWidth: false
            model: ListModel {
                id: modelTypeDeviceText
            }
        }
        SwipeView {
            id: devStackParam
            currentIndex: 0
            anchors.topMargin: 80
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            //                onCurrentIndexChanged: {
            //                    if(devStackParam.currentItem == settingsItem) {
            //                        viewController.getCurrentDevCustomCommand("get current dev settings witout dialog")
            //                    }
            //                }
            Item {
                id: itemProgressTMK24
                x: 6
                y: 6

                SpinBox {
                    id: typeDeviceIdText1
                    x: 324
                    y: 20
                    width: 268
                    height: 40
                    from: 1
                    value: 1
                    to: 255
                    Layout.fillWidth: true
                }

                Label {
                    id: lTypeDeviceId1
                    x: 264
                    y: 37
                    text: qsTr("ID")
                    anchors.verticalCenterOffset: -170
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 294
                }

                TextField {
                    id: passwordText1
                    x: 348
                    y: 80
                    width: 244
                    height: 40
                    placeholderText: "введите пароль"
                    maximumLength: 8
                    echoMode: TextInput.Password
                }

                Label {
                    id: lPassword1
                    x: 264
                    y: 75
                    height: typeDeviceIdText1.height
                    text: qsTr("Пароль")
                    anchors.verticalCenterOffset: -110
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 288
                }

                anchors.fill: parent
            }

            Item {
                id: itemNozzle_v0_00
                ScrollView {
                    clip: true
                    anchors.topMargin: 20
                    anchors.fill: parent
                }

                TextField {
                    id: unuqNameId
                    x: 392
                    y: 20
                    height: 30
                    text: qsTr("")
                    placeholderText: "введите номер"
                }

                Label {
                    id: lTypeDeviceId
                    x: 326
                    y: 20
                    width: 30
                    height: 30
                    text: qsTr("ID")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: passwordText
                    x: 392
                    y: 75
                    height: 30
                    text: ""
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "введите пароль"
                    maximumLength: 8
                    anchors.verticalCenterOffset: -121
                    echoMode: TextInput.Password
                }

                Label {
                    id: lPassword
                    x: 264
                    y: 87
                    height: typeDeviceIdText.height
                    text: qsTr("Пароль")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                    anchors.verticalCenterOffset: -121
                    anchors.leftMargin: 318
                }
                anchors.fill: parent
            }
        }
    }

    ButtonRound {
        id: buttonClose
        anchors.top: gridLayout.bottom
        anchors.left: parent.left
        anchors.rightMargin: 10
        textLine: 2
        textIsCenter: true
        widthBody: 185
        useIcon: true
        iconCode: "\uf00d  "
        name: qsTr("Закрыть")
        y: 128
        anchors.leftMargin: 153
        //            onClicked: {
        //                close()
        //            }
    }
    ButtonRound {
        id: addDevButton
        textLine: 2
        widthBody: 185
        textIsCenter: true
        name: qsTr("Добавить")
        x: -38
        y: 128
        anchors.rightMargin: 453
        useIcon: true
        iconCode: "\uF0FE  "
        anchors.top: gridLayout.bottom
        anchors.right: parent.right
        //            onClicked: {
        //                if (typeDeviceText.currentText.length != 0) {
        //                    viewController.addDeviceToConnection(typeDeviceText.currentText, typeDeviceIdText.value.toString(), passwordText.text)
        //                    close()
        //                }
        //            }
    }

    //    function setListAvailableDevices(list) {
    //        console.log("AddDevice: " + list);
    //        typeDeviceText.model.clear()
    //        for(var i=0; i<list.length; i++) {
    //            typeDeviceText.model.append({text: list[i]})
    //        }
    //        typeDeviceText.currentIndex = 0
    //    }
}
