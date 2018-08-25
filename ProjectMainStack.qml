import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0

Item {
    id: projectMainLayout

    signal deviceButtonClicked(var index)

    anchors.fill: parent
    //    width: 850
    //    height: 500

    function openSession() {
        console.log("ProjectMainStack: Opened session")
        viewForm.projectStack.push(projectDeviceScreen)
        deviceProperties.push(devPropertySerialPort)
    }

    function addInterface(name) {
        console.log("AddInterface: " + name)
        listView.model.append({"name":name,"colorCode":"#81DAF5","identId": "0"})
    }
    Rectangle {
        id: deviceList
        width: 200
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 50
        anchors.top: parent.top
        border.color: "#9899a7"

        ListView {
            id: listView
            clip: true
            maximumFlickVelocity: 0
            highlightFollowsCurrentItem: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: deviceList.left
            anchors.leftMargin: 5
            width: deviceList.width
            height: deviceList.height - 5

            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }

            spacing: 0
            delegate: Item {
                id: item
                height: 50
                width: deviceList.width

                MouseArea {
                    id: mouseArea
                    width: item.width
                    height: item.height

                    Rectangle {
                        id: rect
                        width: item.width - 10
                        height: item.height
                        color: colorCode
                        gradient: Gradient {
                            GradientStop {
                                position: 0
                                color: mouseArea.pressed ? "#ccc" : colorCode
                            }
                            GradientStop {
                                position: 1
                                color: mouseArea.pressed ? "#aaa" : "#FAFAFA"
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
        anchors.left: deviceList.right
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
                    id: deviceProperties
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
                        id:devPropertyLlsTMK24
                    }
                    DevPropertySerialPort {
                        id:devPropertySerialPort
                    }
                }
            }
        }
    }
}
