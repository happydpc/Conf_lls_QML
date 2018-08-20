import timeGame 1.0
import settings 1.0

//import QtQuick 2.9
//import QtQuick.Controls 2.2
//import QtQuick 2.2
import QtQuick.Dialogs 1.2
//import QtQuick 2.4
//import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
//import QtQuick.Layouts 1.3
//import QtGraphicalEffects 1.0
//import QtQuick.Extras 1.4
//import Qt.labs.calendar 1.0
import Qt.labs.platform 1.0
import QtQuick 2.9
import QtQuick.Layouts 1.3

Control {
    id: root

    TimeGame {
        id: timeGame
        onUpdateTime: {
            viewForm.statusBar.text = dateTime
        }
    }

    Settings {
        id: settings
        onGetGamersCountChanged: {

        }
        onUpdateGamerCount: {
        }
    }

    MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                id: menuOpenProject
                text: qsTr("&Open")
                onTriggered: {
                    var component = Qt.createComponent("TestPoligon.qml")
                        if(component.status === Component.Ready) {
                            var dialog = component.createObject(viewForm)
                            dialog.open()
                        } else {
                            console.error(component.errorString())
                        }

//                    testDialog.open()
//                    console.log("Open project dialog"); //
//                    var popupComponent = Qt.createComponent("Test.qml")
//                    var popup2 = popupComponent.createObject(viewForm);
//                    popup2.show()

                    //                    var popupComponent = Qt.createComponent("qrc:/Test.qml")
                    //                    var popup2 = popupComponent.createObject(viewForm, {"parent" : viewForm});
                    //                    popup2.open()
                    //                    var component = Qt.createComponent("Test.qml")
                    //                    var window    = component.createObject(root)
                    //                    window.show()
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ViewForm {
        id: viewForm
        height: parent.height
        width: parent.width
    }
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
