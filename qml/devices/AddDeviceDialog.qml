import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

import "qrc:/qml/miscElems" as MiscElems

Popup {
    id: addDeviceDialog
    modal: true
    width: 700
    height: 600
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
                    keyList.push("devId")
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

    Timer {
        interval: 1000
        running: true
        repeat: false
        onTriggered: {
            tarDevListView.model.append({"deviceTypeName":"TypeDDd","deviceId":"11", "deviceSerialNumber":"SNDDDDDDDDDDD22"})
            tarDevListView.model.append({"deviceTypeName":"Typeaad","deviceId":"12", "deviceSerialNumber":"SNDDDDDDDDDDD33"})
            tarDevListView.model.append({"deviceTypeName":"TypeFFd","deviceId":"13", "deviceSerialNumber":"SNDDDDDDDDDDD44"})
        }
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
        Column {
            anchors.fill: parent
            spacing: 20
            Label {
                id: lTypeDevice
                text: qsTr("Тип устройства")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            ComboBox {
                id: typeDeviceList
                width: parent.width - 10
                height: 40
                model: ListModel {
                    id: modeltypeDeviceList
                }
                onCurrentIndexChanged: {
                    paramStack.setCurrentIndex(currentIndex)
                }
            }
            TabBar {
                id: tabProperty
                height: 25
                anchors.right: parent.right
                anchors.rightMargin: 10
                spacing: 5
                currentIndex: typeAddDeviceView.currentIndex
                font.pointSize: 8
                MiscElems.TabButtonUp {
                    name: "Известный адрес"
                    textLine:1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF274  "
                }
                MiscElems.TabButtonUp {
                    name: "Поиск"
                    textLine:1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF54A  "
                }
            }
            Rectangle {
                width: parent.width
                height: parent.height - 210
                color: "red"
                SwipeView {
                    id:typeAddDeviceView
                    currentIndex: tabProperty.currentIndex
                    interactive: false
                    anchors.fill: parent
                    clip: true
                    Item {
                        Column {
                            anchors.fill: parent
                            spacing: 20
                            Label {
                                id:tarrirDevicesheader
                                text: "Параметры:"
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                            }
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
                    Item {
                        Column {
                            anchors.fill: parent
                            Row{
                                anchors.fill: parent
                                Column{
                                    id:typeAddDeviceFindColumn
                                    anchors.right: parent.right
                                    width: parent.width / 2
                                    height: parent.height
                                    spacing: 20
                                    Label {
                                        text: "Параметры"
                                        anchors.right: parent.right
                                        anchors.rightMargin: 20
                                    }
                                    Row{
                                        anchors.right: parent.right
                                        anchors.rightMargin: 20
                                        spacing: 10
                                        Label {
                                            text: qsTr("От")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        TextField {
                                            id: typeDeviceIdProgressTmk24FindUp
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
                                            text: qsTr("До")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        TextField {
                                            id: typeDeviceIdProgressTmk24FindDown
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
                                }
                                Rectangle {
                                    width: parent.width / 2 + 30
                                    height: parent.height
                                    color: "blue"
                                    anchors.left: parent.left
                                    Label {
                                        id:findDeviceHeader
                                        text: "Найденные устройства:"
                                        anchors.left: parent.left
                                        anchors.leftMargin: 10
                                    }
                                    ListView {
                                        id: tarDevListView
                                        anchors.top: findDeviceHeader.bottom
                                        anchors.topMargin: 10
                                        anchors.bottom: parent.bottom
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        clip: true
                                        ScrollBar.vertical: ScrollBar {
                                            width: 20
                                        }
                                        delegate: Item {
                                            id: tarDevListViewDelegate
                                            height: 100
                                            width: parent.width

                                            Rectangle {
                                                width: parent.width
                                                anchors.left: parent.left
                                                anchors.leftMargin: 10
                                                anchors.rightMargin: 10
                                                height: parent.height
                                                color: "transparent"
                                                TextField {
                                                    id: deviceTypeName
                                                    height: 25
                                                    width: 250
                                                    text: model.deviceTypeName
                                                    font.bold: false
                                                    anchors.top: parent.top
                                                    anchors.topMargin: 5
                                                    anchors.left: parent.left
                                                    readOnly: true
                                                    background: Rectangle {
                                                        anchors.fill: parent
                                                        color: "#ded3d3"
                                                    }
                                                }
                                                TextField {
                                                    id: deviceId
                                                    height: 25
                                                    width: 250
                                                    text: model.deviceId
                                                    font.bold: false
                                                    anchors.top: deviceTypeName.bottom
                                                    anchors.left: parent.left
                                                    readOnly: true
                                                    background: Rectangle {
                                                        anchors.fill: parent
                                                        color: "#c4e7c3"
                                                    }
                                                }
                                                TextField {
                                                    id: deviceSerialNumber
                                                    height: 25
                                                    width: 250
                                                    text: model.deviceSerialNumber
                                                    font.bold: false
                                                    anchors.top: deviceId.bottom
                                                    anchors.left: parent.left
                                                    readOnly: true
                                                    background: Rectangle {
                                                        anchors.fill: parent
                                                        color: "#e7e1c0"
                                                    }
                                                }
                                                Button {
                                                    text: "Убрать"
                                                    width: 100
                                                    height: 30
                                                    anchors.top: parent.top
                                                    anchors.topMargin: 15
                                                    anchors.left: deviceSerialNumber.right
                                                    anchors.leftMargin: 5
                                                    onClicked: {
                                                        var tarList = tarDevListView.model.get(index)
                                                        availableDevListView.model.append(tarList)
                                                        tarDevListView.model.remove(index)
                                                    }
                                                }
                                            }
                                        }
                                        model: ListModel {
                                            id: tarDevListModel
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        MiscElems.ButtonRound {
            id: buttonClose
            anchors.bottom: rectangle.bottom
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

        MiscElems.ButtonRound {
            id: addDevButton
            anchors.bottom: rectangle.bottom
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
                    keyList.push("devId")
                    paramList.push(typeDeviceIdNozzle_v0_00.text)
                    keyList.push("password")
                    paramList.push(passwordNozzle_v0_00.text)
                    viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                    close()
                    break;
                }
            }
        }
        //                Item {
        //                    Column {
        //                        id: itemNozzle_v0_00
        //                        anchors.fill: parent
        //                        spacing: 20
        //                        Row{
        //                            anchors.right: parent.right
        //                            anchors.rightMargin: 20
        //                            spacing: 10
        //                            Label {
        //                                id: lTypeDeviceId1
        //                                text: qsTr("ID")
        //                                anchors.verticalCenter: parent.verticalCenter
        //                            }
        //                            TextField {
        //                                id: typeDeviceIdNozzle_v0_00
        //                                width: 250
        //                                height: 40
        //                                placeholderText: "введите id номер"
        //                                validator: IntValidator{bottom: 1; top: 255;}
        //                                text: "1"
        //                                onFocusChanged: {
        //                                    if(typeDeviceIdNozzle_v0_00.text.length === 0) {
        //                                        typeDeviceIdNozzle_v0_00.text = "1"
        //                                    }
        //                                }
        //                            }
        //                        }
        //                        Row{
        //                            anchors.right: parent.right
        //                            anchors.rightMargin: 20
        //                            spacing: 10
        //                            Label {
        //                                height: 30
        //                                text: qsTr("Пароль")
        //                                anchors.verticalCenter: parent.verticalCenter
        //                            }
        //                            TextField {
        //                                id: passwordNozzle_v0_00
        //                                width: 250
        //                                height: 40
        //                                placeholderText: "введите пароль"
        //                                maximumLength: 8
        //                                echoMode: TextInput.Password
        //                            }
        //                        }
        //                    }
        //                }

        //                        SwipeView {
        //                            id: listAddedDeviceView
        //                            currentIndex: 0
        //                            interactive: false
        //                            height: 300
        //                            width: 300
        //                            clip: true
        //                            Item {
        //                                Column {
        //                                    anchors.fill: parent
        //                                    spacing: 20
        //                                    Row{
        //                                        anchors.right: parent.right
        //                                        anchors.rightMargin: 20
        //                                        spacing: 10
        //                                        Label {
        //                                            id: lTypeDeviceIdProgressTmk24
        //                                            text: qsTr("ID")
        //                                            anchors.verticalCenter: parent.verticalCenter
        //                                        }
        //                                        TextField {
        //                                            id: typeDeviceIdProgressTmk24
        //                                            width: 250
        //                                            height: 40
        //                                            validator: IntValidator{bottom: 1; top: 255;}
        //                                            placeholderText: "введите ID  адрес"
        //                                            text: "1"
        //                                            onFocusChanged: {
        //                                                if(typeDeviceIdProgressTmk24.text.length === 0) {
        //                                                    typeDeviceIdProgressTmk24.text = "1"
        //                                                }
        //                                            }
        //                                        }
        //                                    }
        //                                    Row{
        //                                        anchors.right: parent.right
        //                                        anchors.rightMargin: 20
        //                                        spacing: 10
        //                                        Label {
        //                                            id: lPasswordDeviceProgressTmk24
        //                                            height: 30
        //                                            text: qsTr("Пароль")
        //                                            anchors.verticalCenter: parent.verticalCenter
        //                                        }
        //                                        TextField {
        //                                            id: passwordProgressTmk24
        //                                            width: 250
        //                                            height: 40
        //                                            placeholderText: "введите пароль"
        //                                            maximumLength: 8
        //                                            echoMode: TextInput.Password
        //                                        }
        //                                    }
        //                                }
        //                            }
        //                            Item {
        //                                Column {
        //                                    anchors.fill: parent
        //                                    spacing: 20
        //                                    Row{
        //                                        anchors.right: parent.right
        //                                        anchors.rightMargin: 20
        //                                        spacing: 10
        //                                    }
        //                                }
        //                            }
        //                        }

        //

    }
}
