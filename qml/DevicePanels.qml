import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

Item {
    id: projectDevicePanel
    anchors.fill: parent

    property alias devPropertyLlsTMK24: devPropertyLlsTMK24
    property alias dialogAddDeviceFail : dialogAddDeviceFail
    property alias dialogAddInterfaceFail: dialogAddInterfaceFail

    function setPropertyToSerialPort(listData) {
        devPropertySerialPort.setPropertyValues(listData)
    }
    function remakeInterfaceList(list, status) {
        listInterfaceView.model.clear()
        var size = list.length
        if(size > 0) {
            projectPanels.openDeviceProject()
            for(var i=0; i<size; i++) {
                listInterfaceView.model.append({"text": list[i], "status": status[i]})
            }
        } else {
            projectStack.pop()
        }
    }
    function updateIntefaceListStatus(index, status) {
        listInterfaceView.model.set(index, {"status": status})
        viewController.setChangedIndexInteface(interfaceList.model.index)
    }

    function remakeDeviceList(list, status) {
        listDeviceView.model.clear()
        var size = list.length
        if(size > 0) {
            for(var i=0; i<size; i++) {
                listDeviceView.model.append({"text": list[i], "status": status[i]})
                console.log("list[i] - status = " + status[i])
            }
        } else {
            devicePropertieslistModel1.pop()
        }
    }
    function updateDeviceListStatus(index, status) {
        listDeviceView.model.set(index, {"status": status})
    }
    function devShowPasswordIncorrect(devNameId) {
        dialogPasswordError.messageArg = devNameId
        dialogPasswordError.open()
    }
    function devShowTypeIncorrect(devNameId) {
        dialogTypeError.messageArg = devNameId
        dialogTypeError.open()
    }

    Rectangle {
        id: interfaceList
        width: 200
        height: portOrDeviceStack.height / 2 - 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 50
        border.color: "#9899a7"

        ListView {
            id: listInterfaceView
            anchors.leftMargin: 0
            anchors.fill: parent
            clip: true
            maximumFlickVelocity: 0
            highlightFollowsCurrentItem: true

            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }

            delegate: Item {
                id: item
                height: 50
                width: interfaceList.width

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                MouseArea {
                    id: mouseArea
                    width: item.width
                    height: item.height
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    Rectangle {
                        id: rect
                        width: item.width - 2
                        anchors.left: parent.left
                        anchors.leftMargin: 1
                        height: item.height
                        color: colorCode
                        gradient: Gradient {
                            GradientStop {
                                position: 0
                                color: isCurrent ? (mouseArea.pressed ? "#416FE1" : "#416FE1") : (mouseArea.pressed ? "#8FAAFA" : "#84A4F5")
                            }
                            GradientStop {
                                position: 1
                                color: isCurrent ? (mouseArea.pressed ? "#416FE1" : "#416FE1") : (mouseArea.pressed ? "#416FE1" : "#C0D0F7")
                            }
                        }
                        Label {
                            id: buttonText
                            text: model.text
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {
                        console.log("Interface List clicked ")
                        if (mouse.button === Qt.LeftButton) {
                            view.currentIndex = model.index
                            devicePropertieslistModel1.pop()
                            viewController.setChangedIndexInteface(model.index)
                        } else {
                            dialogRemoveSerialPort.open()
                        }
                    }
                }
            }
            model: ListModel {
                id: listModel
            }
        }
    }

    Rectangle {
        id: parametersRect
        color: "#ffffff"
        anchors.left: interfaceList.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 50
        border.color: "#9899a7"
        anchors.top: parent.top

        StackView {
            id: portOrDeviceStack
            anchors.fill: parent

            Rectangle {
                id: currentStateRectangle
                color: "#fdfdfd"
                anchors.fill: parent
                border.width: 1
                border.color: "#9899a7"

                StackView {
                    id: devicePropertieslistModel1
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 1
                    anchors.rightMargin: 1
                    clip: true
                    initialItem: devPropertySerialPort

                    DevPropertyLlsTMK324 {
                        id: devPropertyLlsTMK24
                    }
                    DevPropertySerialPort {
                        id: devPropertySerialPort
                    }
                }
            }
        }
    }

    Rectangle {
        id: deviceList
        x: -1
        y: 427
        height: portOrDeviceStack.height / 2 - 10
        anchors.right: parametersRect.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        border.color: "#9899a7"
        anchors.left: parent.left

        ListView {
            id: listDeviceView
            anchors.leftMargin: 0
            anchors.fill: parent
            clip: true
            maximumFlickVelocity: 0
            highlightFollowsCurrentItem: false

            ScrollBar.vertical: ScrollBar {
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Vertical
                width: 10
            }

            delegate: Item {
                id: item_2
                height: 50
                width: deviceList.width
                property var viewDevice: ListView.view
                property var isCurrentDevice: ListView.isCurrentItem

                MouseArea {
                    id: mouseArea_2
                    width: item_2.width
                    height: item_2.height
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    Rectangle {
                        id: rect_2
                        width: item_2.width - 2
                        anchors.left: parent.left
                        anchors.leftMargin: 1
                        height: item_2.height
                        color: colorCode
                        gradient: Gradient {
                            GradientStop {
                                position: 0
                                color: isCurrentDevice ? (mouseArea_2.pressed ? "#416FE1" : "#416FE1") : (mouseArea_2.pressed ? "#8FAAFA" : "#84A4F5")
                            }
                            GradientStop {
                                position: 1
                                color: isCurrentDevice ? (mouseArea_2.pressed ? "#416FE1" : "#416FE1") : (mouseArea_2.pressed ? "#416FE1" : "#C0D0F7")
                            }
                        }
                        Label {
                            id: buttonText_2
                            text: model.text
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 15
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Image {
                            id: icon
                            height: 32
                            width: 32
                            anchors.right: parent.right
                            anchors.rightMargin: 15
                            source: model.status === 1 ? "/new/icons/images/icon/normal.png" : "/new/icons/images/icon/no_normal.png"
                        }
                    }
                    onClicked: {
                        console.log("DeviceList clicked ")
                        if (mouse.button === Qt.LeftButton) {
                            viewDevice.currentIndex = model.index
                            devicePropertieslistModel1.push(devPropertyLlsTMK24)
                            viewController.setChangedIndexDevice(model.index)
                        } else {
                            dialogRemoveDevice.open()
                        }
                    }
                }
            }
            model: ListModel {
                id: listModel_2
            }
        }
        anchors.leftMargin: 10
    }

    Dialog {
        id: dialogRemoveDevice
        visible: false
        title: "Удаление устройства"
        standardButtons: StandardButton.Close | StandardButton.Apply
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Удалить устройство?"
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            viewController.removeActiveDevice()
            close()
        }
    }

    Dialog {
        id: dialogRemoveSerialPort
        visible: false
        title: "Удаление последовательного порта"
        standardButtons: StandardButton.Close | StandardButton.Apply
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Удалить последовательный порт?"
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            viewController.removeActiveConnectionSerialPort()
            close()
        }
    }

    Dialog {
        id: dialogAddDeviceFail
        visible: false
        title: "Добавление устройства"
        standardButtons: StandardButton.Close
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Не получилось добавить устройство\nТакой адрес уже используется"
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
                text: qsTr("Настроечный пароль устройства %1 не совпадает\nс установленным в устройстве\nЭто устройство удалено из списка!").arg(dialogPasswordError.messageArg)
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
}
