import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

import "qrc:/qml/miscElems" as MiscElems

Popup {
    modal: true
    width: 700
    height: 600
    clip: true

    signal resultMessage(var res)

    property string modeFind_idle:          "mode_idle"
    property string modeFind_add_once:      "mode_add_once"
    property string modeFind_add_finder:    "mode_add_finder"
    property string modeFind: modeFind_idle

    function setListAvailableDevices(list) {
        console.log("AddDevice: " + list);
        typeDeviceList.model.clear()
        for(var i=0; i<list.length; i++) {
            typeDeviceList.model.append({text: list[i]})
        }
        typeDeviceList.currentIndex = 0
    }

    function setResultCheckDevice(devTypeName, devId, devSn, result) {
        var paramList = []
        var keyList = []
        switch(modeFind) {
        case modeFind_idle: break
        case modeFind_add_once:
            if(result === true) {
                switch(typeDeviceList.currentIndex) {
                case 0:
                    if(typeDeviceList.currentText.length !== 0) {
                        keyList.push("id")
                        paramList.push(typeDeviceIdProgressTmk24.text)
                        keyList.push("password")
                        paramList.push(typeDevicePasswordProgressTmk24.text)
                        viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                        close()
                    }
                    break;
                case 1:
                    break;
                }
            } else {
                resultMessage("Не удалось добавить устройство\nТак как оно не ответило на запрос")
                close()
            }
            break;

        case modeFind_add_finder:
            switch(typeDeviceList.currentIndex) {
            case 0:
                if(result) {
                    findDevListView.model.append({"deviceTypeName":devTypeName,"deviceId":devId, "deviceSerialNumber":devSn})
                }
                if(typeFindStartButton.findIdValues !== parseInt(typeDeviceIdProgressTmk24FindUp.text)) {
                    typeDeviceProgressProgressTmk24.value = 100 / parseInt(typeDeviceIdProgressTmk24FindUp.text) * typeFindStartButton.findIdValues;
                    typeDeviceProgressProgressTmk24.visible = true
                    typeDeviceIdProgressTmk24FindDown.readOnly = true
                    typeDeviceIdProgressTmk24FindUp.readOnly = true
                    typeFindStartButton.findIdValues++
                    keyList.push("id")
                    paramList.push(typeFindStartButton.findIdValues.toString())
                    keyList.push("password")
                    paramList.push("")
                    viewController.checkDeviceFromConnection(typeDeviceList.currentText, keyList, paramList)
                } else {
                    typeDeviceProgressProgressTmk24.value = 0;
                    typeDeviceProgressProgressTmk24.visible = false
                    typeFindStartButton.enabled = true
                    typeFindStopButton.enabled = false
                    typeDeviceIdProgressTmk24FindDown.readOnly = false
                    typeDeviceIdProgressTmk24FindUp.readOnly = false
                }
                break;
            case 1:
                close()
                break;
            }
            break;
        }
    }

    onClosed: {
        modeFind = modeFind_idle
        findDevListView.model.clear()
        typeDeviceProgressProgressTmk24.value = 0;
        typeDeviceProgressProgressTmk24.visible = false
        typeFindStartButton.enabled = true
        typeFindStopButton.enabled = false
        typeDeviceIdProgressTmk24FindDown.readOnly = false
        typeDeviceIdProgressTmk24FindUp.readOnly = false
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
                enabled: modeFind !== modeFind_add_finder
                model: ListModel {
                    id: modeltypeDeviceList
                }
            }
            SwipeView {
                id:typeDevicesView
                currentIndex: typeDeviceList.currentIndex
                interactive: false
                height: parent.height
                width: parent.width
                Item { // progress tmk24
                    Column {
                        spacing: 10
                        anchors.fill: parent
                        TabBar {
                            id: tabPropertyProgressTmk24
                            height: 25
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            spacing: 5
                            currentIndex: typeAddDeviceViewProgressTmk24.currentIndex
                            font.pointSize: 8
                            enabled: modeFind !== modeFind_add_finder
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
                            color: "#ffffff"
                            SwipeView {
                                id:typeAddDeviceViewProgressTmk24
                                currentIndex: tabPropertyProgressTmk24.currentIndex
                                interactive: false
                                anchors.fill: parent
                                clip: true
                                Item {
                                    Column {
                                        anchors.fill: parent
                                        spacing: 20
                                        Label {
                                            text: "Параметры:"
                                            anchors.right: parent.right
                                            anchors.rightMargin: 20
                                        }
                                        Row{
                                            anchors.right: parent.right
                                            anchors.rightMargin: 20
                                            spacing: 10
                                            Label {
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
                                                id: typeDevicePasswordProgressTmk24
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
                                                    text: "Параметры адресов поиска"
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
                                                Row{
                                                    anchors.right: parent.right
                                                    anchors.rightMargin: 20
                                                    spacing: 10
                                                    Label {
                                                        text: qsTr("До")
                                                        anchors.verticalCenter: parent.verticalCenter
                                                    }
                                                    TextField {
                                                        id: typeDeviceIdProgressTmk24FindUp
                                                        width: 250
                                                        height: 40
                                                        validator: IntValidator{bottom: 1; top: 255;}
                                                        placeholderText: "введите ID  адрес"
                                                        text: "254"
                                                        onFocusChanged: {
                                                            if(typeDeviceIdProgressTmk24.text.length === 0) {
                                                                typeDeviceIdProgressTmk24.text = "1"
                                                            }
                                                        }
                                                    }
                                                }
                                                ProgressBar {
                                                    id:typeDeviceProgressProgressTmk24
                                                    width: 250
                                                    height: 40
                                                    anchors.right: parent.right
                                                    anchors.rightMargin: 20
                                                    visible: false
                                                    from: 0
                                                    to: 100
                                                }
                                                Button {
                                                    id:typeFindStartButton
                                                    anchors.right: parent.right
                                                    anchors.rightMargin: 20
                                                    width: 200
                                                    height: 50
                                                    text: "Искать"
                                                    property int findIdValues: 1
                                                    onClicked: {
                                                        typeFindStopButton.enabled = true
                                                        typeFindStartButton.enabled = false
                                                        var keyList = []
                                                        var paramList = []
                                                        modeFind = modeFind_add_finder
                                                        findIdValues = parseInt(typeDeviceIdProgressTmk24FindDown.text)
                                                        findDevListView.model.clear()
                                                        keyList.push("id")
                                                        paramList.push(findIdValues)
                                                        keyList.push("password")
                                                        paramList.push("")
                                                        viewController.checkDeviceFromConnection(typeDeviceList.currentText, keyList, paramList)

                                                    }
                                                }
                                                Button {
                                                    id:typeFindStopButton
                                                    anchors.right: parent.right
                                                    anchors.rightMargin: 20
                                                    width: 200
                                                    height: 50
                                                    text: "Остановить"
                                                    enabled: false
                                                    onClicked: {
                                                        typeFindStartButton.enabled = true
                                                        typeFindStopButton.enabled = false
                                                        modeFind = modeFind_idle
                                                    }
                                                }
                                            }
                                            Rectangle {
                                                width: parent.width / 2 + 30
                                                height: parent.height
                                                color: "#ffffff"
                                                anchors.left: parent.left
                                                Label {
                                                    id:findDeviceHeader
                                                    text: "Найденные устройства:"
                                                    anchors.left: parent.left
                                                    anchors.leftMargin: 10
                                                }
                                                ListView {
                                                    id: findDevListView
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
                                                        id: findDevListViewDelegate
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
                                                                    var tarList = findDevListView.model.get(index)
                                                                    findDevListView.model.remove(index)
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
                }
                Item { // nozzle rev 0.0
                    Column {
                        spacing: 10
                        anchors.fill: parent
                        TabBar {
                            id: tabPropertyNozzle_v0_0
                            height: 25
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            spacing: 5
                            currentIndex: typeAddDeviceViewNozzle_v0_0.currentIndex
                            font.pointSize: 8
                            MiscElems.TabButtonUp {
                                name: "Известный адрес"
                                textLine:1
                                widthBody: 155
                                useIcon: true
                                iconCode: "\uF274  "
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: parent.height - 210
                            color: "#ffffff"
                            SwipeView {
                                id:typeAddDeviceViewNozzle_v0_0
                                currentIndex: 0
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
                                                text: qsTr("ID")
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                            TextField {
                                                id: typeDeviceIdNozzle_v0_0
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
                                                id: typeDevicePasswordNozzle_v0_0
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
                modeFind = modeFind_add_finder
                typeDeviceList.currentIndex = 0
                findDevListView.model.clear()
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
                case 0: // progress tmk24
                    switch(typeAddDeviceViewProgressTmk24.currentIndex) {
                    case 0: // simple add device
                        keyList.push("id")
                        paramList.push(typeDeviceIdProgressTmk24.text)
                        keyList.push("password")
                        paramList.push(typeDevicePasswordProgressTmk24.text)
                        viewController.checkDeviceFromConnection(typeDeviceList.currentText, keyList, paramList)
                        modeFind = modeFind_add_once
                        break;
                    case 1: // find device
                        var size = findDevListView.count
                        var deviceId = []
                        for(var i=0; i<size; i++) {
                            var item = findDevListView.model.get(i)
                            keyList = []
                            paramList = []
                            keyList.push("id")
                            paramList.push(item.deviceId)
                            keyList.push("password")
                            paramList.push("")
                            viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                        }
                        modeFind = modeFind_idle
                        typeDeviceProgressProgressTmk24.value = 0
                        typeDeviceProgressProgressTmk24.visible = false
                        typeFindStartButton.enabled = true
                        typeFindStopButton.enabled = false
                        typeDeviceIdProgressTmk24FindDown.readOnly = false
                        typeDeviceIdProgressTmk24FindUp.readOnly = false
                        findDevListView.model.clear()
                        close()
                        break;
                    }
                    break;
                case 1: // nozle rev 0_0
                    keyList.push("id")
                    paramList.push(typeDeviceIdNozzle_v0_0.text)
                    keyList.push("password")
                    paramList.push(typeDevicePasswordNozzle_v0_0.text)
                    viewController.addDeviceToConnection(typeDeviceList.currentText, keyList, paramList)
                    modeFind = modeFind_idle
                    typeDeviceProgressProgressTmk24.visible = false
                    findDevListView.model.clear()
                    break;
                }
            }
        }
    }
}
