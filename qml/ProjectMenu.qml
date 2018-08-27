import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick 2.2
import QtQuick.Dialogs 1.1
import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import Qt.labs.calendar 1.0

MenuBar {
    Menu {
        title: qsTr("File")
        MenuItem {
            text: qsTr("&Open")
            onTriggered: console.log("Open action triggered");
        }
        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}

//Rectangle{
//    id:rrrr
//Menu {
//    title: "Проект"
//    MenuItem {
//        text: "Открыть"
//        //                    stackView.
//        //                    onMenuChanged: {

//        //                    }
//    }
//    MenuItem {
//        text: "Закрыть"
//    }
//    MenuItem {
//        text: "Выйти"
//    }
//}
//}

//MenuBar {
//    id: projectMenu
////    MenuBar {
//        //        id:projectMenu
//        Menu {
//            //            id: projectMenu
//            title: "Проект"
//            MenuItem {
//                text: "Открыть"
//                onMenuChanged: {

//                }
//            }
//            MenuItem {
//                text: "Закрыть"
//            }
//            MenuItem {
//                text: "Выйти"
//            }
//        }

//        Menu {
//            title: "Настройка"
//            //            MenuItem {
//            //                text: "Cut"
//            //            }
//        }
////    }
//}

//ApplicationWindow {
//    id: projectMenu

//    Button {
//        anchors.centerIn: parent
//        text: qsTr("Click me")
//        onClicked: {
//            var component = Qt.createComponent("Test.qml")
//            var window    = component.createObject(root)
//            window.show()
//        }
//    }
//}

// {
//    Button {
//          anchors.centerIn: parent
//          text: qsTr("Click me")
//          onClicked: {
//              var component = Qt.createComponent("Test.qml")
//              var window    = component.createObject(root)
//              window.show()
//          }
//      }
//}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
