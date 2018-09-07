import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0

Item {
    id: projectDevicePanel
    anchors.fill: parent

    property alias devPropertyLlsTMK24: devPropertyLlsTMK24

    function setPropertyToSerialPort(listData) {
        devPropertySerialPort.setPropertyValues(listData)
    }
    function remakeInterfaceList(list, status) {
        listInterfaceView.model.clear()
        var size = list.length
        for(var i=0; i<size; i++) {
            listInterfaceView.model.append({"text": list[i], "status": status[i]})
        }
    }
    function remakeDeviceList(list, status) {
        listDeviceView.model.clear()
        var size = list.length
        for(var i=0; i<size; i++) {
            listDeviceView.model.append({"text": list[i], "status": status[i]})
        }
    }
    function updateDeviceListStatus(index, status) {
        listDeviceView.model.set(index, {"status": status})
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
                            text: model.text
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {
                        console.log("DeviceList clicked ")
                        view.currentIndex = model.index
                        devicePropertieslistModel1.pop()
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
                        viewDevice.currentIndex = model.index
                        devicePropertieslistModel1.push(devPropertyLlsTMK24)
                        viewController.setChangedIndexDevice(model.index)
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
