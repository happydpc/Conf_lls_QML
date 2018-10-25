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
    property int interfaceIndex: 0

    property var deviceItemArray: [[]];
    property int deviceIndex: 0

    property alias dialogAddInterfaceFail: dialogAddInterfaceFail
    property alias messageOperationError: messageOperationError
    property int indexItem_Logo: 0
    property int indexItem_Intefaces: 1
    property int indexItem_Devices: 2

    // *************  logo   **************/
    function setActiveLogoPanel() {
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

            var devItem = Qt.createQmlObject('import QtQuick.Controls 2.4;SwipeView{id:deviceView_1;anchors.fill:parent;interactive:false;clip: true;}', deviceRootView);
            deviceRootView.addItem(devItem)
            break;
        default: break;
        }
    }

    function intefaceDeleted(ioIndex) {
        interfaceIndex = ioIndex
        interfaceView.removeItem(interfaceIndex)
        interfaceItemArray.splice(interfaceIndex, interfaceIndex+1)
        if(interfaceItemArray.length <=0) {
            modeSelectView.setCurrentIndex(indexItem_Logo)
        }
    }

    function setActiveInterfacePanelType(ioType, ioIndex) {
        switch(ioType.toLowerCase()) {
        case "serial":
            interfaceIndex = ioIndex
            for(var len=0; len<interfaceItemArray.length; len++) {
                interfaceItemArray[len].visible = false
            }
            interfaceItemArray[interfaceIndex].visible = true
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
            interfaceView.setCurrentIndex(interfaceIndex)
            break;
        default: break;
        }
   }

    function setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty) {
        modeSelectView.setCurrentIndex(indexItem_Intefaces)
        interfaceIndex = ioIndex
        interfaceView.setCurrentIndex(interfaceIndex)
        interfaceItemArray[interfaceIndex].setPropertyValues(keyProperty, valueProperty)
    }

    function intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result) {
        interfaceIndex = ioIndex
        interfaceItemArray[interfaceIndex].setResultCheckDevice(devTypeName, devId, devSn, result)
    }

    // *************  devices   **************/
    function deviceAdded(devType, devKeyProperty, devValueProperty) {
        switch(devType.toLowerCase()) {
        case "progress tmk24":
            var componentQml = Qt.createComponent("qrc:/qml/devices/DevPropertyProgressTmk24.qml");
            var item = componentQml.createObject(deviceRootView)
            item.setInitProperty(devKeyProperty, devValueProperty)
            deviceRootView.setCurrentIndex(interfaceIndex)
            var it = deviceRootView.itemAt(interfaceIndex)
            it.addItem(item)
            deviceItemArray[interfaceIndex].push(item);
            modeSelectView.setCurrentIndex(indexItem_Devices)
            break;
        case "nozzle rev 0.0":
            break;
        default: break;
        }
    }

    function deviceDeleted(devIndex) {
        deviceView.removeItem(devIndex)
        deviceItemArray[interfaceIndex].slice(devIndex-1, devIndex)
        if(deviceItemArray[interfaceIndex].length <=0) {
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
        }
        if(interfaceItemArray.length <=0) {
            modeSelectView.setCurrentIndex(indexItem_Logo)
        }
    }

    function setActiveDevicePanelType(devType, devIndex) {
        for(var len=0; len<deviceItemArray[interfaceIndex].length; len++) {
            deviceItemArray[interfaceIndex][len].visible = false
        }
        deviceRootView.setCurrentIndex(interfaceIndex)
        var it = deviceRootView.itemAt(interfaceIndex)
        deviceItemArray[interfaceIndex][devIndex].visible = true
        it.setCurrentIndex(devIndex)
        modeSelectView.setCurrentIndex(indexItem_Devices)
    }

    function setDevCustomCommandExecuted(typeDev, devIndex, keys, args, ackMessageIsVisible) {
        deviceItemArray[interfaceIndex][devIndex].setCustomCommandExecuted(keys, args, ackMessageIsVisible)
    }

    // *************  message **************/
    function showDeviceAddError(devTypeName, errorMessage) {
        dialogAddDeviceFail.message = errorMessage
        dialogAddDeviceFail.open()
    }

    function setReadyProperties(devIndex, typeDev, keys, values) {
        deviceItemArray[interfaceIndex][devIndex].setPropertyes(keys, values)
        deviceRootView.setCurrentIndex(interfaceIndex)
        var it = deviceRootView.itemAt(interfaceIndex)
        it.setCurrentIndex(devIndex)
    }

    function setReadyPeriodicData(devIndex, typeDev, keys, values) {
        deviceRootView.setCurrentIndex(interfaceIndex)
        var it = deviceRootView.itemAt(interfaceIndex)
        it.setCurrentIndex(devIndex)
        var id = deviceItemArray[interfaceIndex][devIndex].getId()
        if(getDevIsThis(id, keys, values)) {
            deviceItemArray[interfaceIndex][devIndex].insertPeriodicData(keys, values)
        }
    }

    function setDevConnected(devIndex, typeDev) {
        deviceItemArray[interfaceIndex][devIndex].setConnected()
    }

    function setDevReady(devIndex, typeDev) {
        deviceItemArray[interfaceIndex][devIndex].setReady()
    }

    function setDevDisconnected(devIndex, typeDev) {
        deviceItemArray[interfaceIndex][devIndex].setDisconnected()
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

    function addDeviceLog(devIndex, codeMessage, message) {
        deviceItemArray[interfaceIndex][devIndex].addLogMessage(codeMessage, message)
    }

    function addLogMessage(codeMessage, message) {
        switch(typeDev.toLowerCase()) {
        case "progress tmk24":
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.addLogMessage(codeMessage, message)
            break;
        case "nozzle rev 0.0":
            break;
        default: break;
        }
    }

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
