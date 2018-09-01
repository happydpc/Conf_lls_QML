import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0

Item {
    id: projectDevicePanel
    anchors.fill: parent

    function addInterface(name) {
        console.log("AddInterface: " + name)
        listInterfaceView.model.append({"name":name,"colorCode":"#81DAF5","identId": "0"})
    }

    function addDevice(name) {
        console.log("addDevice: " + name)
        listDeviceView.model.append({"name":name,"colorCode":"#D5F9AE","identId": "0"})
    }

    function setCurrentActiveInterface(nameInterface, indexInterface, activeDeviceIndex) {
//        StackView {
//            id: devicePropertieslistModel1
//            anchors.left: parent.left
//            anchors.leftMargin: 0
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 0
//            anchors.right: parent.right
//            anchors.top: parent.top
//            anchors.topMargin: 1
//            anchors.rightMargin: 1
//            initialItem: devPropertySerialPort

//            DevPropertyLlsTMK324 {
//                id: devPropertyLlsTMK24
//            }
//            DevPropertySerialPort {
//                id: devPropertySerialPort
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

            spacing: 0
            delegate: Item {
                id: item
                height: 50
                width: interfaceList.width

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
                                color: mouseArea.pressed ? "#666CE1" : colorCode
                            }
                            GradientStop {
                                position: 1
                                color: mouseArea.pressed ? "#666CE1" : "#FAFAFA"
                            }
                        }
                        Label {
                            id: buttonText
                            text: name
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            visible: false
                            text: identId
                        }
                    }
                    //                    onClicked: {
                    //                        console.log("DeviceList clicked " + " " + identId)
                    //                        deviceButtonClicked(identId)
                    //                    }
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

            spacing: 0
            delegate: Item {
                id: item_2
                height: 50
                width: deviceList.width

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
                                color: mouseArea_2.pressed ? "#6CB215" : colorCode
                            }
                            GradientStop {
                                position: 1
                                color: mouseArea_2.pressed ? "#6CB215" : "#FAFAFA"
                            }
                        }
                        Label {
                            id: buttonText_2
                            text: name
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            visible: false
                            text: identId
                        }
                    }
                    //                    onClicked: {
                    //                        console.log("DeviceList clicked " + " " + identId)
                    //                        deviceButtonClicked(identId)
                    //                    }
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
