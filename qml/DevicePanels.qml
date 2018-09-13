import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11

Item {
    id: projectDevicePanel
    anchors.fill: parent

    property alias devPropertyProgressTmk24: devPropertyProgressTmk24
    //    property alias devPropertyProgressTmk4ux: devPropertyProgressTmk4ux
    property alias dialogAddDeviceFail : dialogAddDeviceFail
    property alias dialogAddInterfaceFail: dialogAddInterfaceFail
    property alias devicePropertieslistModel1: devicePropertieslistModel1
    property alias messageOperationError: messageOperationError

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
        //        listDeviceView.model.clear()
        //        var size = list.length
        //        if(size > 0) {
        //            for(var i=0; i<size; i++) {
        //                listDeviceView.model.append({"text": list[i], "status": status[i]})
        //                console.log("list[i] - status = " + status[i])
        //            }
        //        } else {
        //            devicePropertieslistModel1.pop()
        //        }

        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})
        listInterfaceView.model.append({"text": "name", "status": status[1]})

        //        wrapper.listDeviceView_2.model.append({"text":"dddd","status":0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
        //        wrapper.listDeviceView_2.model.append({"text": "TMK-xxxx", "status": 0})
    }
    function updateDeviceListStatus(index, status) {
        //        listDeviceView.model.set(index, {"status": status})
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
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.bottom: parent.bottom
        border.color: "#ffffff"

        ListView {
            id: listInterfaceView
            anchors.fill: parent
            clip: true
            maximumFlickVelocity: 0
            highlightFollowsCurrentItem: true

            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }
            delegate: treeDelegate

            model: ListModel {
                id: listModel
            }

            //Компонент делегата
            Component {
                id: treeDelegate
                Item {
                    id: wrapper
                    height: activeParent === false ? 30 : devRect.heightActive
                    width: interfaceList.width
                    property bool activeParent: false
                    Rectangle {
                        id:devRect
                        anchors.fill: parent
                        visible: wrapper.activeParent
                        property int heightActive: listDeviceView_2.count * 100
                        ListView {
                            id: listDeviceView_2
                            anchors.leftMargin: 0
                            anchors.fill: parent
                            anchors.topMargin: 20
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
                                id: item_2_2
                                height: 25
                                width: deviceList.width
                                property var viewDevice: ListView.view
                                property var isCurrentDevice: ListView.isCurrentItem

                                MouseArea {
                                    id: mouseArea_2_2
                                    width: item_2_2.width
                                    height: item_2_2.height
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                                    Rectangle {
                                        id: rect_2_2
                                        width: item_2_2.width - 2
                                        anchors.left: parent.left
                                        anchors.leftMargin: 1
                                        height: item_2_2.height
                                        color: "transparent"
                                        Label {
                                            id: buttonText_2_2
                                            text: model.text
                                            font.bold: false
                                            color: isCurrentDevice ? (mouseArea_2_2.pressed ? "#416FE1" : "#416FE1") : (mouseArea_2_2.pressed ? "#416FE1" : "#C0D0F7")
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Image {
                                            id: icon_2
                                            height: 24
                                            width: 24
                                            anchors.right: parent.right
                                            anchors.top: parent.top
                                            anchors.rightMargin: 15
                                            source: model.status === 1 ? "/new/icons/images/icon/normal.png" : "/new/icons/images/icon/no_normal.png"
                                        }
                                    }
                                    onClicked: {
                                        console.log("DeviceList clicked ")
                                        if (mouse.button === Qt.LeftButton) {
                                            viewDevice.currentIndex = model.index
                                            devicePropertieslistModel1.push(devPropertyProgressTmk24)
                                            devPropertyProgressTmk24.setNoReady()
                                            viewController.setChangedIndexDevice(model.index)
                                        } else {
                                            dialogRemoveDevice.open()
                                        }
                                    }
                                }
                            }
                            model: ListModel {
                                id: listModel_2_2
                            }
                        }
                    }
                    //Область для отображения данных элемента
                    Text {
                        id: nameTextElement_2
                        text: model.text
                        verticalAlignment: "AlignVCenter"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: wrapper.top
                        //Отлавливаем нажатие мышкой и открываем/закрываем элемент
                        MouseArea {
                            anchors.fill: parent
                            height: 50
                            onClicked: {
                                console.log("clicked MouseArea")
                                if(wrapper.activeParent === true) {
                                    wrapper.activeParent = false
                                } else {
                                    wrapper.activeParent = true
                                    listDeviceView_2.model.append({"text":"1111122"})
                                    listDeviceView_2.model.append({"text":"1111122"})
                                    listDeviceView_2.model.append({"text":"1111122"})
                                    listDeviceView_2.model.append({"text":"1111122"})
                                    listDeviceView_2.model.append({"text":"1111122"})
                                    listDeviceView_2.model.append({"text":"1111122"})
                                }
                            }
                        }
                    }
                }
            }
        }
        //        ListView {
        //            id: listInterfaceView
        //            anchors.fill: parent
        //            clip: true
        //            maximumFlickVelocity: 0
        //            highlightFollowsCurrentItem: true

        //            ScrollBar.vertical: ScrollBar {
        //                id: scrollDeviceList
        //                width: 20
        //            }

        //            delegate: Item {
        //                id: item
        //                height: 30
        //                width: interfaceList.width

        //                property var view: ListView.view
        //                property var isCurrent: ListView.isCurrentItem

        //                MouseArea {
        //                    id: mouseArea
        //                    width: item.width
        //                    height: item.height
        //                    acceptedButtons: Qt.LeftButton | Qt.RightButton

        //                    Rectangle {
        //                        id: rect
        //                        width: item.width - 2
        //                        anchors.left: parent.left
        //                        anchors.leftMargin: 1
        //                        height: item.height
        //                        color: "transparent"
        //                        Image {
        //                            id: iconConnection
        //                            height: 24
        //                            width: 24
        //                            anchors.left: parent.left
        //                            anchors.top: parent.top
        //                            source: isCurrent ? "/new/icons/images/icon/connectionSelected.png" : "/new/icons/images/icon/connectionNoSelected.png"
        //                        }
        //                        Label {
        //                            id: buttonText
        //                            text: model.text
        //                            font.bold: false
        //                            color: isCurrent ? (mouseArea.pressed ? "#3598fa" : "#3598fa") : (mouseArea.pressed ? "#3598fa" : "#d1dfe9")
        //                            anchors.left: iconConnection.left
        //                            anchors.leftMargin: 45
        //                            anchors.verticalCenter: parent.verticalCenter
        //                        }
        //                    }
        //                    onClicked: {
        //                        console.log("Interface List clicked ")
        //                        if (mouse.button === Qt.LeftButton) {
        //                            view.currentIndex = model.index
        //                            devicePropertieslistModel1.pop()
        //                            viewController.setChangedIndexInteface(model.index)
        //                        } else {
        //                            dialogRemoveSerialPort.open()
        //                        }
        //                    }
        //                }
        //            }
        //            model: ListModel {
        //                id: listModel
        //            }
        //        }
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

                    DevPropertyProgressTmk24 {
                        id: devPropertyProgressTmk24
                        //                        property bool isActive: false
                    }
                    //                    DevPropertyProgressTmk4ux {
                    //                        id: devPropertyProgressTmk4ux
                    ////                        property bool isActive: false
                    //                    }
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
                height: 25
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
                        color: "transparent"
                        Label {
                            id: buttonText_2
                            text: model.text
                            font.bold: false
                            color: isCurrentDevice ? (mouseArea_2.pressed ? "#416FE1" : "#416FE1") : (mouseArea_2.pressed ? "#416FE1" : "#C0D0F7")
                            anchors.left: parent.left
                            anchors.leftMargin: 15
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Image {
                            id: icon
                            height: 24
                            width: 24
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.rightMargin: 15
                            source: model.status === 1 ? "/new/icons/images/icon/normal.png" : "/new/icons/images/icon/no_normal.png"
                        }
                    }
                    onClicked: {
                        console.log("DeviceList clicked ")
                        if (mouse.button === Qt.LeftButton) {
                            viewDevice.currentIndex = model.index
                            devicePropertieslistModel1.push(devPropertyProgressTmk24)
                            devPropertyProgressTmk24.setNoReady()
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
