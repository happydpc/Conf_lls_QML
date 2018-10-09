import QtQuick 2.9
import QtQuick.Controls 2.4

Component {
    id:projectMainStack

    Rectangle {
        id: projectDevicePanel
        color: "transparent"

        Rectangle {
            id: deviceList
            border.color: "#E0ECF8"
            height: parent.height - menuMain.height - viewForm.statusBarRecangle.height - deviceList.anchors.topMargin
            width: 200

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

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
                height: deviceList.height -5

                ScrollBar.vertical: ScrollBar {
                    id:scrollDeviceList
                    width: 20
                }

                spacing: 0
                delegate: Item {
                    id:item
                    height: 50
                    width: deviceList.width

                    MouseArea {
                        id:mouseArea
                        width: item.width
                        height: item.height
                        pressAndHoldInterval: 1000
                        Rectangle {
                            id:rect
                            width: item.width - 10
                            height: item.height
                            color: colorCode
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: mouseArea.pressed ? "#ccc" : colorCode}
                                GradientStop { position: 1 ; color: mouseArea.pressed ? "#aaa" : "#FAFAFA" }
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
                                text:identId
                            }
                        }
                        onClicked: {
                            for (var i = 0, l = listView.contentItem.children.length; i < l; i++) {
                                console.log("DeviceList clicked " + i + " " + identId)
                            }
                            if(parametersStackItem.depth <= 0) {
                                parametersStackItem.push(deviceControlLlsTmk24)
                            } else if(parametersStackItem.depth ===1) {
                                parametersStackItem.push(deviceControlLlsTmk24_2)
                            } else {
                                parametersStackItem.pop()
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: parametersRectangle
            color: "#fdfdfd"
            border.color: "#81a8b9"
            anchors.right: currentStateRectangle.left
            anchors.rightMargin: 10
            anchors.left: deviceList.left
            anchors.leftMargin: -projectDevicePanel.width + deviceList.width + currentStateRectangle.width + 20

            StackView {
                id: parametersStackItem
                anchors.fill: parent
                initialItem: comPortControl
                clip: true

                Control {
                    id: comPortControl
                    Rectangle {
                        anchors.fill: parent
                        color: "#33ffff"
                    }
                }

                Control {
                    id: deviceControlLlsTmk24
                    Rectangle {
                        anchors.fill: parent
                        color: "#ff222f"
                    }
                }

                Control {
                    id: deviceControlLlsTmk24_2
                    Rectangle {
                        anchors.fill: parent
                        color: "#55222f"
                    }
                }
            }
        }
    }
}
