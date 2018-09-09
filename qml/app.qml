import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 1100
    height: 700
    title: qsTr("Tabs")

    View {
        id: view
        height: parent.height
        width: parent.width
    }
}

//import QtQuick.Controls 2.3
//import QtQuick 2.0

//ApplicationWindow {
//    visible: true
//    width: 1100
//    height: 700
//    title: qsTr("Tabs")
//    color: "#e7e9eb"

//    Rectangle {
//        id: interfaceList
//        width: 500
//        height: 500
//        visible: true

//        ListView {
//            id: view

//            anchors.margins: 10
//            anchors.fill: parent
//            spacing: 10
//            model: dataModel

//            delegate: Rectangle {
//                width: view.width
//                height: 100
//                color: model.color

//                Row {
//                    anchors.margins: 10
//                    anchors.left: parent.left
//                    anchors.verticalCenter: parent.verticalCenter
//                    spacing: 10

//                    Repeater {
//                        model: texts
//                        delegate: Text {
//                            verticalAlignment: Text.AlignVCenter
//                            renderType: Text.NativeRendering
//                            text: model.text
//                        }
//                    }
//                }
//            }

//            ListModel {
//                id: dataModel

//                ListElement {
//                    color: "orange"
//                    text: 1
//                }
//                ListElement {
//                    color: "skyblue"
//                    text: "second"
//                }
//            }
//        }
//    }
//}
