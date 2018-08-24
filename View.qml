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
