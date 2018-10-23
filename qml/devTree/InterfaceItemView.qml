import QtQuick 2.0

Row{
    id: itemView
    signal eventSelectInterface()
    signal eventDeleteInterface();

    Rectangle {
        id: itemRectRoot
        width: 10
        height: 20
        Text {
            id:itemRectIcon
            text: " \uf1e6"
            anchors.left: itemRectRoot.left
            anchors.leftMargin: 5
            color: "#a7b6c6"
            font { family: "customFont";}
            font.pointSize: 14
        }
        Text{
            id:interfaceName
            text: modelData.content
            color: modelData.isCurrent ? "#46e342" : "#3598fa"
            anchors.left: itemRectIcon.left
            anchors.leftMargin: 30
            MouseArea{
                id:aread
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    modelData.isCurrent = true
                    if(modelData.hasChild) {
                        modelData.isOpen = !modelData.isOpen;
                    }
                    eventSelectInterface()
                }
            }
        }
        Text {
            id:removeItemIcon
            text: " \uf1f8"
            anchors.left: interfaceName.right
            anchors.leftMargin: 10
            color: deleteInterfaceMouse.isFocused === true ? "#58fce4" : "#dbd9d9"
            font { family: "customFont";}
            font.pointSize: 14
            width: 28
            height: 28
            MouseArea {
                id:deleteInterfaceMouse
                acceptedButtons: Qt.LeftButton
                anchors.fill: parent
                hoverEnabled: true
                property bool isFocused: false
                onEntered: {
                    isFocused = true
                }
                onExited: {
                    isFocused = false
                }
                onClicked: {
                    modelData.isCurrent = true
                    if(mouse.button === Qt.LeftButton) {
                        eventDeleteInterface()
                    }
                }
            }
        }
        Text {
            id: childRectIndicator
            anchors.left: removeItemIcon.right
            text: " \uf2db"
            color: "#a7b6c6"
            font { family: "customFont";}
            font.pointSize: 14
            visible: (modelData.hasChild) ? true : false
        }
    }

    Column{
        id:column
        spacing: 20
        Rectangle {
            width: 10
            height: 10
            color: "transparent"
        }
        Loader{
            source: modelData.isOpen ? "DeviceTree.qml" : "DeviceItemEmpty.qml"
        }
    }
}


//    Rectangle {
//        id: itemRectRoot
//        width: 210
//        height: 20
//        Text {
//            id:itemRectIcon
//            text: " \uf1e6"
//            anchors.left: itemRectRoot.left
//            anchors.leftMargin: 5
//            color: modelData.isConnected === true ? "#58fce4" : "#dbd9d9"
//            font { family: "customFont";}
//            font.pointSize: 14
//            width: 28
//            height: 28
//        }
//        MouseArea{
//            id:aread
//            height: 20
//            width: 120
//            acceptedButtons: Qt.LeftButton | Qt.RightButton
//            onClicked: {
//                modelData.isCurrent = true
//                if (mouse.button === Qt.LeftButton) {
//                    if(modelData.hasChild) {
//                        modelData.isOpen = !modelData.isOpen;
//                    }
//                    eventClickLeft()
//                } else {
//                    eventClickRight()
//                }
//            }
//        }
//        Text {
//            id: childRectIndicator
//            anchors.right: parent.right
//            text: " \uf2db"
//            color: "#a7b6c6"
//            font { family: "customFont";}
//            font.pointSize: 14
//            visible: (modelData.hasChild) ? true : false
//        }
//        Text {
//            id:removeItemIcon
//            text: " \uf1f8"
//            anchors.right: childRectIndicator.left
//            color: deleteInterfaceMouse.isFocused === true ? "#58fce4" : "#dbd9d9"
//            font { family: "customFont";}
//            font.pointSize: 14
//            width: 28
//            height: 28
//            MouseArea {
//                id:deleteInterfaceMouse
//                acceptedButtons: Qt.LeftButton
//                anchors.fill: parent
//                hoverEnabled: true
//                property bool isFocused: false
//                onEntered: {
//                    isFocused = true
//                }
//                onExited: {
//                    isFocused = false
//                }
//                onClicked: {
//                    modelData.isCurrent = true
//                    if(mouse.button === Qt.LeftButton) {
//                        eventDeleteInterface()
//                    }
//                }
//            }
//        }
//    }

//    Column{
//        id:column
//        spacing: 20
//        Rectangle {
//            width: 10
//            height: 10
//            color: "transparent"
//        }
//        Loader{
//            source: modelData.isOpen ? "DeviceTree.qml" : "DeviceItemEmpty.qml"
//        }
//    }
//}
