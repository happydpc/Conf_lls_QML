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
        try {
            if(interfaceItemArray !== undefined) {
                while(interfaceItemArray.length !== 0) {
                    intefaceDeleted(0)
                }
            }
            modeSelectView.setCurrentIndex(indexItem_Logo)
            gc();
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    // *************  interfaces  **************/
    function intefaceAdded(ioType, keyProperty, valueProperty) {
        try {
            switch(ioType.toLowerCase()) {
            case "serial":
                var componentQml = Qt.createComponent("qrc:/qml/interfaces/DevPropertySerialPort.qml");
                var item = componentQml.createObject(interfaceView)
                item.setPropertyValues(keyProperty, valueProperty)
                interfaceItemArray.push(item);
                interfaceView.addItem(item)
                modeSelectView.setCurrentIndex(indexItem_Intefaces)
                var devItem = Qt.createQmlObject('import QtQuick.Controls 2.4;SwipeView{interactive:false;clip:true;}', deviceRootView);
                deviceItemArray.push([])
                deviceRootView.addItem(devItem)
                break;
            default: break;
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function intefaceDeleted(ioIndex) {
        try {
            interfaceView.removeItem(ioIndex)
            var removeIem = interfaceItemArray[ioIndex]
            removeIem.removeAll()
            removeIem.destroy()
            delete interfaceItemArray[ioIndex]
            interfaceItemArray.splice(ioIndex, ioIndex+1)
            while(deviceItemArray[ioIndex].length !== 0) {
                deviceDeleted(ioIndex, 0)
            }
            if(interfaceItemArray.length <=0) {
                modeSelectView.setCurrentIndex(indexItem_Logo)
            }
            gc();
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setActiveInterfacePanelType(ioType, ioIndex) {
        try {
            switch(ioType.toLowerCase()) {
            case "serial":
                for(var len=0; len<interfaceItemArray.length; len++) {
                    interfaceItemArray[len].visible = false
                }
                if(interfaceItemArray !== undefined) {
                    if(interfaceItemArray[ioIndex] !== undefined) {
                        interfaceItemArray[ioIndex].visible = true
                    }
                }
                modeSelectView.setCurrentIndex(indexItem_Intefaces)
                interfaceView.setCurrentIndex(ioIndex)
                break;
            default: break;
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty) {
        try {
            modeSelectView.setCurrentIndex(indexItem_Intefaces)
            interfaceView.setCurrentIndex(ioIndex)
            if(interfaceItemArray !== undefined) {
                if(interfaceItemArray[ioIndex] !== undefined) {
                    interfaceItemArray[ioIndex].setPropertyValues(keyProperty, valueProperty)
                }
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result) {
        try {
            if(interfaceItemArray !== undefined) {
                if(interfaceItemArray[ioIndex] !== undefined) {
                    interfaceItemArray[ioIndex].setResultCheckDevice(devTypeName, devId, devSn, result)
                }
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    // *************  devices   **************/
    function deviceAdded(ioIndex, devType, devKeyProperty, devValueProperty) {
        var componentQml = undefined
        try {
            switch(devType.toLowerCase()) {
            case "progress tmk24":
                componentQml = Qt.createComponent("qrc:/qml/devices/DevPropertyProgressTmk24.qml");
                break;
            case "nozzle rev 0.0":
                componentQml = Qt.createComponent("qrc:/qml/devices/DevPropertyNozzle_v_0_00.qml");
                break;
            default: break;
            }
            if(componentQml != undefined) {
                var devSwipe = deviceRootView.itemAt(ioIndex)
                var item = componentQml.createObject(devSwipe)
                item.setInitProperty(devKeyProperty, devValueProperty)
                devSwipe.addItem(item)
                deviceItemArray[ioIndex].push(item);
                deviceRootView.setCurrentIndex(ioIndex)
                devSwipe.setCurrentIndex(devSwipe.length-1)
                modeSelectView.setCurrentIndex(indexItem_Devices)
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function deviceDeleted(ioIndex, devIndex) {
        try {
            if(deviceItemArray !== undefined) {
                if(deviceItemArray[ioIndex] !== undefined) {
                    if(deviceItemArray[ioIndex][devIndex] !== undefined) {
                        var it = deviceRootView.itemAt(ioIndex)
                        var subItem = it.itemAt(devIndex)
                        it.removeItem(devIndex)
                        subItem.removeAll()
                        subItem.destroy();
                        delete deviceItemArray[ioIndex][devIndex]
                        deviceItemArray[ioIndex].splice(devIndex, devIndex+1)
                        if(deviceItemArray[ioIndex].length === 0) {
                            modeSelectView.setCurrentIndex(indexItem_Intefaces)
                        } else {
                            deviceRootView.setCurrentIndex(ioIndex) // ???
                            it = deviceRootView.itemAt(ioIndex)
                            it.setCurrentIndex(deviceItemArray[ioIndex].size-1)
                        }
                        gc();
                    }
                }
            }
            if(interfaceItemArray.length <=0) {
                modeSelectView.setCurrentIndex(indexItem_Logo)
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setActiveDevicePanelType(devType, ioIndex, devIndex) { /****/
        try {
            deviceRootView.setCurrentIndex(ioIndex) // ????
            var it = deviceRootView.itemAt(ioIndex)
            it.setCurrentIndex(devIndex)
            modeSelectView.setCurrentIndex(indexItem_Devices)
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setDevCustomCommandExecuted(typeDev, ioIndex, devIndex, keys, args) { /****/
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].setCustomCommandExecuted(keys, args)
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    // *************  message **************/
    function showDeviceAddError(devTypeName, errorMessage) {
        try {
            dialogAddDeviceFail.message = errorMessage
            dialogAddDeviceFail.open()
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setDevReadyProperties(typeDev, ioIndex, devIndex, keys, values) {
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].setPropertyes(keys, values)
            }
            deviceRootView.setCurrentIndex(ioIndex) // ????
            var it = deviceRootView.itemAt(ioIndex)
            it.setCurrentIndex(devIndex)
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setReadyPeriodicData(typeDev, ioIndex, devIndex, keys, values) {
        try {
            deviceRootView.setCurrentIndex(ioIndex) // ???
            var it = deviceRootView.itemAt(ioIndex)
            it.setCurrentIndex(devIndex)
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                var id = deviceItemArray[ioIndex][devIndex].getId()
                if(getDevIsThis(id, keys, values)) {
                    deviceItemArray[ioIndex][devIndex].insertPeriodicData(keys, values)
                }
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setDevConnected(ioIndex, devIndex, typeDev) { /****/
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].setConnected()
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setDevReady(ioIndex, devIndex, typeDev) { /****/
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].setReady()
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function setDevDisconnected(ioIndex, devIndex, typeDev) { /****/
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].setDisconnected()
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function getDevIsThis(id, keys, values, result) {
        try {
            for(var i=0; i<keys.length; i++) {
                if(keys[i] === "id") {
                    if(values[i] === id) {
                        return true
                    }
                }
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
        return false
    }

    function isAvailableSubIndex(array, ioIndex, devIndex) {
        if(array.length >= ioIndex) {
            if(array[ioIndex] !== undefined) {
                if(array[ioIndex].length >= devIndex) {
                    if(array[ioIndex][devIndex] !== undefined) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    function setDevShowMessage(typeDev, messageHeader, message) {
        try {
            switch(typeDev.toLowerCase()) {
            case "progress tmk24":
                projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.devShowMessage(messageHeader, message)
                break;
            case "nozzle rev 0.0":
                projectPanel.devicePanel.devicePropertyPanel.devPropertyNozzle_v_0_00.devShowMessage(messageHeader, message)
                break;
            default: break;
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    function addDeviceLog(ioIndex, devIndex, codeMessage, message) {
        try {
            if(isAvailableSubIndex(deviceItemArray, ioIndex, devIndex)) {
                deviceItemArray[ioIndex][devIndex].addLogMessage(codeMessage, message)
            }
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    // TODO: type!
    function devShowTypeIncorrect(typeDev, devNameId) {
        try {
            dialogTypeError.messageArg = devNameId
            dialogTypeError.open()
        } catch (error) {
            console.log ("Error loading QML : ")
            for (var i = 0; i < error.qmlErrors.length; i++) {
                console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                console.log("fileName: " + error.qmlErrors[i].fileName)
                console.log("message: " + error.qmlErrors[i].message)
            }
        }
    }

    Rectangle {
        id: parametersRect
        color: "#ffffff"
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
                            id:logoPane
                        }
                    }
                }
                Item {
                    SwipeView {
                        id: interfaceView
                        interactive: false
                        anchors.fill: parent
                        clip: true
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
                    spacing: 50
                    Text {
                        text: qsTr("Доступна новая версия программы\nРекомендуется скачать инсталятор, удалить текущую версию и установить новую!\n")
                    }
                    Text {
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
            standardButtons: StandardButton.Ok
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
            onAccepted: {
                close()
            }
        }

        Dialog {
            id: dialogTypeError
            visible: false
            title: "Ошибка типа устройства"
            standardButtons: StandardButton.Ok
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
            onAccepted: {
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
