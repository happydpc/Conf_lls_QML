import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    id: root

    ViewForm {
        id: viewForm
        height: parent.height
        width: parent.width
    }

    MenuBar {
        id: menuMain
        anchors.left: parent.left
        anchors.leftMargin: 10
        Menu {
            title: qsTr("Connection")
            MenuItem {
                id: menuOpenProject
                text: qsTr("Add")
                onTriggered: {
                    var component = Qt.createComponent("/SerialPort.qml")
                    if(component.status === Component.Ready) {
                        var dialog = component.createObject(viewForm)
                        dialog.onAcceptButtonEvent.connect(function() {
                            console.log("Accept open connection")
                            viewForm.projectStack.push(viewForm.projectDeviceScreen)
                            dialog.close()
                        })
                        dialog.onCloseButtonEvent.connect(function() {
                            console.log("abort button connection")
                            viewForm.projectStack.pop()
                            dialog.close()
                        })
                        dialog.open()
                    } else {
                        console.error(component.errorString())
                    }
                }
            }
            MenuItem {
                text: qsTr("Close projects")
                enabled: viewForm.projectStack.depth > 1
                onTriggered: {
                    viewForm.projectStack.pop()
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        id: deviceList
        border.color: "#E0ECF8"
        height: parent.height - menuMain.height - viewForm.statusBarRecangle.height - deviceList.anchors.topMargin
        width: 200
        anchors.top: menuMain.bottom
        anchors.topMargin: 5

        ListView {
            id: listView
            clip: true
            maximumFlickVelocity: 0
            anchors.top: deviceList.top
            anchors.topMargin: 5
            anchors.right: deviceList.right
            anchors.rightMargin: 5
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
                    Rectangle {
                        id:rect
                        width: item.width - 10
                        height: item.height
                        color: colorCode
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: mouseArea.pressed ? "#ccc" : colorCode}
                            GradientStop { position: 1 ; color: mouseArea.pressed ? "#aaa" : "#FAFAFA" }
                        }
                        radius: 10
                        Label {
                            text: name
                            font.bold: false
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {

                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "COM9"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#FAFAFA"
                }

                ListElement {
                    name: "ТМК3.24 (ID-2)"
                    colorCode: "#FAFAFA"
                }

                ListElement {
                    name: "COM21"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#FAFAFA"
                }
                ListElement {
                    name: "COM9"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#FAFAFA"
                }

                ListElement {
                    name: "ТМК3.24 (ID-2)"
                    colorCode: "#FAFAFA"
                }

                ListElement {
                    name: "COM21"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#FAFAFA"
                }
                ListElement {
                    name: "COM9"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#F2F2F2"
                }

                ListElement {
                    name: "ТМК3.24 (ID-2)"
                    colorCode: "#F2F2F2"
                }

                ListElement {
                    name: "COM21"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#F2F2F2"
                }
            }
        }
    }

    //    Button {
    //        text: "Test control"
    //        onClicked: {
    //            if(viewForm.projectStack.depth > 1) {
    //                viewForm.projectStack.pop()
    //            } else {
    //                viewForm.projectStack.push(viewForm.projectDeviceScreen)
    //            }
    //        }
    //    }
}

//MessageDialog {
//    id: messageDialog
//    title: "May I have your attention please"
//    text: "It's so cool that you are using Qt Quick."
//    onAccepted: {
//        console.log("And of course you could only agree.")
//        Qt.quit()
//    }
//    Component.onCompleted: visible = true
//}

//Button {
//      anchors.centerIn: parent
//      text: qsTr("Click me")

//      onClicked: {
//          var component = Qt.createComponent("Test.qml")
//          var window    = component.createObject(root)
//          window.show()
//      }
//  }

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
