import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0

Item {
    id: projectDevicePanel
    anchors.fill: parent

    //----------     public
    function addInterface(name) {
        console.log("AddInterface: " + name)
        listInterfaceView.model.append({"text":name})
    }
    function addDevice(name) {
        console.log("addDevice: " + name)
        listDeviceView.model.append({"text":name})
    }
    function setPropertyToSerialPort(listData) {
        devPropertySerialPort.setPropertyValues(listData)
        devicePropertieslistModel1.pop()
        remakeDeviceList()
    }
    function setCurrentDataToDevTmk24(listData) {
        devPropertyLlsTMK24.setUpdateCurrentValues(listData)
    }
    function setCurrentDataToDevTmk13(listData) { // TODO:!!!
    }

    //----------     private
    function remakeDeviceList() {
        listDeviceView.model.clear()
        var devListSize = viewController.getDeviceCount()
        console.log("devile list size: " + devListSize)
        for(var index=0; index<devListSize; index++) {
            var dev = viewController.getDeviceHeaderByIndex(index);
            listDeviceView.model.append({"text": dev[0]})
        }
    }

    function setDevPropertyToPanel() {
        var data = viewController.getCurrentDevPropertyByIndex(listDeviceView.model.index)
        devPropertyLlsTMK24.setDevProperty(data)
        devicePropertieslistModel1.push(devPropertyLlsTMK24)
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
                            text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {
                        console.log("DeviceList clicked ")
                        view.currentIndex = model.index
                        viewController.setChangedIndexInteface(model.index)
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
            highlightFollowsCurrentItem: true

            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList_2
                width: 20
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
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {
                        console.log("DeviceList clicked ")
                        viewDevice.currentIndex = model.index
                        viewController.setChangedIndexDevice(model.index)
                        setDevPropertyToPanel()
                    }
                }
            }
            model: ListModel {
                id: listModel_2
            }
        }
        anchors.leftMargin: 10
    }
}

/*##^## Designer {
    D{i:14;anchors_height:242;anchors_width:200}D{i:13;anchors_height:262;anchors_width:200}
D{i:32;anchors_height:345;anchors_width:200}D{i:31;anchors_height:257;anchors_width:365}
}
 ##^##*/
