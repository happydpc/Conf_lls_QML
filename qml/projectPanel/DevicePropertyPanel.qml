import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11
import "qrc:/qml/devices"
import "qrc:/qml/interfaces"

Rectangle {
    id: projectDevicePanel
    property var interfaceItemArray: []
    property var deviceItemArray: [];

    property alias dialogAddInterfaceFail: dialogAddInterfaceFail
    property alias messageOperationError: messageOperationError
    property alias updateVersionDialog: updateVersionDialog
    property int indexItem_Logo: 0
    property int indexItem_Intefaces: 1
    property int indexItem_Devices: 2

    // *************  logo   **************/
    function setActiveLogoPanel() {
        modeSelectView.setCurrentIndex(indexItem_Logo)
    }

    // *************  full clear before load session **************/
    function setCrearAllItems() {
        interfaceItemArray = []
        deviceItemArray = []
        while(deviceRootView.count !== 0) {
            deviceRootView.removeItem(0)
            interfaceView.removeItem(0)
        }
        modeSelectView.setCurrentIndex(indexItem_Logo)
    }

    // *************  interfaces  **************/
    function intefaceAdded(ioType, keyProperty, valueProperty) {
        switch(ioType.toLowerCase()) {
        case "serial":
            var componentQml = Qt.createComponent("qrc:/qml/interfaces/DevPropertySerialPort.qml");
            var item = componentQml.createObject(interfaceView)
            item.setPropertyValues(keyProperty, valueProperty)
            interfaceView.addItem(item)
            interfaceItemArray.push(item);
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
            var devItem = Qt.createQmlObject('import QtQuick.Controls 2.4;SwipeView{anchors.fill:parent;interactive:false;clip: true;}', deviceRootView);
            deviceItemArray.push([])
            deviceRootView.addItem(devItem)
            break;
        default: break;
        }
    }

    function intefaceDeleted(ioIndex) {
        interfaceView.removeItem(ioIndex)
        interfaceItemArray.splice(ioIndex, ioIndex+1)
        if(interfaceItemArray.length <=0) {
            modeSelectView.setCurrentIndex(indexItem_Logo)
        }
        deviceItemArray.splice(ioIndex, ioIndex+1)
        deviceRootView.removeItem(ioIndex)
    }

    function setActiveInterfacePanelType(ioType, ioIndex) {
        switch(ioType.toLowerCase()) {
        case "serial":
            for(var len=0; len<interfaceItemArray.length; len++) {
                interfaceItemArray[len].visible = false
            }
            interfaceItemArray[ioIndex].visible = true
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
            interfaceView.setCurrentIndex(ioIndex)
            break;
        default: break;
        }
    }

    function setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty) {
        modeSelectView.setCurrentIndex(indexItem_Intefaces)
        interfaceView.setCurrentIndex(ioIndex)
        interfaceItemArray[ioIndex].setPropertyValues(keyProperty, valueProperty)
    }

    function intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result) {
        interfaceItemArray[ioIndex].setResultCheckDevice(devTypeName, devId, devSn, result)
    }

    // *************  devices   **************/
    function deviceAdded(ioIndex, devType, devKeyProperty, devValueProperty) {
        switch(devType.toLowerCase()) {
        case "progress tmk24":
            var componentQml = Qt.createComponent("qrc:/qml/devices/DevPropertyProgressTmk24.qml");
            var item = componentQml.createObject(deviceRootView.currentItem)
            item.setInitProperty(devKeyProperty, devValueProperty)
            deviceRootView.setCurrentIndex(ioIndex)
            var it = deviceRootView.currentItem
            it.addItem(item)
            deviceItemArray[ioIndex].push(item);
            deviceRootView.setCurrentIndex(ioIndex)
            modeSelectView.setCurrentIndex(indexItem_Devices)
            break;
        case "nozzle rev 0.0":
            break;
        default: break;
        }
    }

    function deviceDeleted(ioIndex, devIndex) {
        var it = deviceRootView.itemAt(ioIndex)
        it.removeItem(devIndex)
        deviceItemArray[ioIndex].splice(devIndex, devIndex+1)
        if(deviceItemArray[ioIndex].length === 0) {
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
        } else {
            deviceRootView.setCurrentIndex(ioIndex) // ???
            it = deviceRootView.itemAt(ioIndex)
            it.setCurrentIndex(deviceItemArray[ioIndex].size-1)
        }
        if(interfaceItemArray.length <=0) {
            modeSelectView.setCurrentIndex(indexItem_Logo)
        }
    }

    function setActiveDevicePanelType(devType, ioIndex, devIndex) { /****/
        for(var len=0; len<deviceRootView.count; len++) {
            for(var lenSub=0; lenSub<deviceItemArray[len].length; lenSub++) {
                deviceItemArray[len][lenSub].visible = false
            }
        }
        deviceRootView.setCurrentIndex(ioIndex) // ????
        var it = deviceRootView.itemAt(ioIndex)
        it.setCurrentIndex(devIndex)
        it.visible = true
        deviceItemArray[ioIndex][devIndex].visible = true
        modeSelectView.setCurrentIndex(indexItem_Devices)
    }

    function setDevCustomCommandExecuted(typeDev, ioIndex, devIndex, keys, args, ackMessageIsVisible) { /****/
        deviceItemArray[ioIndex][devIndex].setCustomCommandExecuted(keys, args, ackMessageIsVisible)
    }

    // *************  message **************/
    function showDeviceAddError(devTypeName, errorMessage) {
        dialogAddDeviceFail.message = errorMessage
        dialogAddDeviceFail.open()
    }

    function setDevReadyProperties(typeDev, ioIndex, devIndex, keys, values) { /****/
        deviceItemArray[ioIndex][devIndex].setPropertyes(keys, values)
        deviceRootView.setCurrentIndex(ioIndex) // ????
        var it = deviceRootView.itemAt(ioIndex)
        it.setCurrentIndex(devIndex)
    }

    function setReadyPeriodicData(typeDev, ioIndex, devIndex, keys, values) { /****/
        deviceRootView.setCurrentIndex(ioIndex) // ???
        var it = deviceRootView.itemAt(ioIndex)
        it.setCurrentIndex(devIndex)
        var id = deviceItemArray[ioIndex][devIndex].getId()
        if(getDevIsThis(id, keys, values)) {
            deviceItemArray[ioIndex][devIndex].insertPeriodicData(keys, values)
        }
    }

    function setDevConnected(ioIndex, devIndex, typeDev) { /****/
        deviceItemArray[ioIndex][devIndex].setConnected()
    }

    function setDevReady(ioIndex, devIndex, typeDev) { /****/
        deviceItemArray[ioIndex][devIndex].setReady()
    }

    function setDevDisconnected(ioIndex, devIndex, typeDev) { /****/
        deviceItemArray[ioIndex][devIndex].setDisconnected()
    }

    function getDevIsThis(id, keys, values, result) {
        for(var i=0; i<keys.length; i++) {
            if(keys[i] === "id") {
                if(values[i] === id) {
                    return true
                }
            }
        }
        return false
    }

    function setDevShowMessage(typeDev, messageHeader, message) {
        switch(typeDev.toLowerCase()) {
        case "progress tmk24":
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.devShowMessage(messageHeader, message)
            break;
        case "nozzle rev 0.0":
            projectPanel.devicePanel.devicePropertyPanel.devPropertyNozzle_v_0_00.devShowMessage(messageHeader, message)
            break;
        default: break;
        }
    }

    function addDeviceLog(ioIndex, devIndex, codeMessage, message) {
        deviceItemArray[ioIndex][devIndex].addLogMessage(codeMessage, message)
    }

    function addLogMessage(codeMessage, message) {}

    // TODO: type!
    function devShowTypeIncorrect(typeDev, devNameId) {
        dialogTypeError.messageArg = devNameId
        dialogTypeError.open()
    }

    Rectangle {
        id: parametersRect
        color: "transparent"
        anchors.fill: parent
        anchors.top: parent.top

        Rectangle {
            color: "#ffffff"
            anchors.fill: parent
            border.width: 1
            border.color: "#9899a7"

            SwipeView {
                id: modeSelectView
                anchors.fill: parent
                interactive: false
                currentIndex: 0
                clip: true

                Item {
                    Rectangle {
                        id: logoSubPanel
                        anchors.fill: parent
                        height: 500
                        width: 500
                        color: "red"
                        LogoPanel {

                        }
                    }
                }
                Item {
                    SwipeView {
                        id: interfaceView
                        interactive: false
                        anchors.fill: parent
                        clip: true
                        DevPropertySerialPort {
                            id: devPropertySerialPort
                        }
                    }
                }
                Item {
                    SwipeView {
                        id: deviceRootView
                        anchors.fill: parent
                        interactive: false
                        clip: true
                    }
                }
            }
        }

        Dialog {
            id: dialogAddDeviceFail
            visible: false
            title: "Добавление устройства"
            property string message: ""
            standardButtons: StandardButton.Accept
            Rectangle {
                color: "transparent"
                implicitWidth: 400
                implicitHeight: 200
                Text {
                    text: dialogAddDeviceFail.message
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

        Dialog {
            id: dialogAddInterfaceFail
            visible: false
            title: "Добавление интерфейса"
            standardButtons: StandardButton.Close
            Rectangle {
                color: "transparent"
                implicitWidth: 350
                implicitHeight: 100
                Text {
                    text: "Не получилось добавить интерфейс\nВозможно такой интерфейс уже используется\nили ресурс не доступен"
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

        Dialog {
            id:updateVersionDialog
            visible: false
            title: "Проверка обновлений"
            standardButtons: StandardButton.Close
            property string url: ""
            Rectangle {
                color: "transparent"
                implicitWidth: 500
                implicitHeight: 80
                Column{
                    anchors.fill: parent
                    spacing: 10
                    Text {
                        text: qsTr("Доступна новая версия программы\nРекомендуется скачать инсталятор, удалить текущую версию и установить новую!\n")
                    }
                    Text {
                        anchors.centerIn: parent
                        text: "<a href='" + updateVersionDialog.url + "'>Нажмите здесь</a>"
                        onLinkActivated: Qt.openUrlExternally(link)
                    }
                }
            }
        }

        Dialog {
            id: dialogPasswordError
            visible: false
            title: "Ошибка пароля"
            standardButtons: StandardButton.Apply
            property string messageArg: ""
            width: 500
            height: 150
            Rectangle {
                color: "transparent"
                anchors.fill: parent
                Text {
                    text: qsTr("Настроечный пароль устройства %1 не совпадает\nс установленным в устройстве\nЗапись настроек не возможна!").arg(dialogPasswordError.messageArg)
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
            onApply: {
                close()
            }
        }

        Dialog {
            id: dialogTypeError
            visible: false
            title: "Ошибка типа устройства"
            standardButtons: StandardButton.Apply
            property string messageArg: ""
            width: 500
            height: 150
            Rectangle {
                color: "transparent"
                anchors.fill: parent
                Text {
                    text: qsTr("Тип устройства не совпадает с заявленным при создании [%1]\nЭто устройство удалено из списка!").arg(dialogTypeError.messageArg)
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
            onApply: {
                close()
            }
        }

        Dialog {
            id: messageOperationError
            visible: false
            title: "Ошибка операции"
            standardButtons: StandardButton.Close
            property string message: ""
            Rectangle {
                color: "transparent"
                implicitWidth: 450
                implicitHeight: 100
                Text {
                    text: messageOperationError.message
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }
    }
}
