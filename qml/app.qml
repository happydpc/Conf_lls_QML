import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11

ApplicationWindow {
    visible: true
    width: 1100
    height: 700
    title: qsTr("Конфигуратор ДУТ (Beta 0.0)")


        View {
            id: view
            height: parent.height
            width: parent.width
        }
}


//    property int subRectangleTopEx: 0

//    Rectangle {
//        anchors.fill: parent
//        border.color: "red"

//        Component.onCompleted: {
//            deviceListModel.append({"name":"name1Dev"})
//            deviceListModel.append({"name":"name2Dev"})
//            deviceListModel.append({"name":"name3Dev"})
//            deviceListView.model.append({"name":"name4Dev"})
//            deviceListView.model.append({"name":"name5Dev"})

//            interfaceListView.model.append({"name":"name3Interface"})
//            interfaceListView.model.append({"name":"name4Interface"})
//            interfaceListView.model.append({"name":"name5Interface"})
//        }

//        ListView {
//            id: interfaceListView
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.rightMargin: parent.width/2
//            anchors.left: parent.left
//            anchors.right: parent.right

//            delegate: Component {
//                Item {
//                    id: wrapper
//                    height: wrapper.childIsVisible === true ? childRectangle.height : 50
//                    width: interfaceListView.width
//                    property bool childIsVisible: false
//                    property int heightWithDevPanel: 0
//                      Rectangle {
//                        id:subRectangle
//                        height: 50
//                        anchors.top: parent.top
//                        anchors.left: parent.left
//                        anchors.right: parent.right
//                        color: "gray"
//                    }
//                    Text {
//                        id: nameTextElement
//                        text: name
//                        verticalAlignment: "AlignVCenter"
//                        anchors.left: wrapper.left
//                        anchors.leftMargin: 50
//                        anchors.top: wrapper.top
//                        anchors.right: parent.right
//                    }
//                    MouseArea {
//                        id:mouseArea
//                        anchors.fill: parent
//                        onClicked: {
//                            if(wrapper.childIsVisible == false) {
//                                wrapper.childIsVisible = true
//                                wrapper.height = childRectangle.height
//                                deviceListView.visible = true
//                                subRectangleTopEx = parent.y
//                            } else {
//                                wrapper.childIsVisible = false
//                                wrapper.height = 50
//                                deviceListView.visible = false
//                            }
//                            console.log("clicked =" + deviceListView.height)
//                        }
//                    }
//                    Rectangle {
//                        id:childRectangle
//                        height: deviceListView.height
//                        width: interfaceListView.width
//                        anchors.top: parent.top
//                        anchors.topMargin: subRectangle.height
//                        color: "green"
//                        visible: wrapper.childIsVisible
//                    }
//                }
//            }
//            model : ListModel {
//                id:interfaceListModel
//            }
//        }
//    }

//    ListView {
//        id: deviceListView
//        visible: false
//        anchors.top: parent.top
//        anchors.topMargin: subRectangleTopEx
////        anchors.bottom: parent.bottom
//        height: 100
//        anchors.leftMargin: parent.width/2
//        anchors.left: parent.left
//        anchors.right: parent.right

//        delegate: Component {
//            Item {
//                height: 50
//                width: deviceListView.width
//                Rectangle {
//                    id:subRectangle
//                    height: parent.height
//                    anchors.top: parent.top
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    color: "gray"
//                }
//                Text {
//                    id: nameTextElement
//                    text: name
//                    verticalAlignment: "AlignVCenter"
//                    anchors.left: parent.left
//                    anchors.leftMargin: 50
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom
//                    anchors.right: parent.right
//                }
//            }
//        }
//        model : ListModel {
//            id:deviceListModel
//        }
//    }
//}
