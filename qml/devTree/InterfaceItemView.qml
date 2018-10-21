import QtQuick 2.0

Row{
    id: itemView

    signal eventClickLeft()
    signal eventClickRight();

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
        MouseArea{
            id:aread
            height: 20
            width: 120
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                modelData.isCurrent = true
                if (mouse.button === Qt.LeftButton) {
                    if(modelData.hasChild) {
                        modelData.isOpen = !modelData.isOpen;
                    }
                    eventClickLeft()
                } else {
                    eventClickRight()
                }
            }
        }
        Text{
            id:interfaceName
            text: modelData.content
            color: modelData.isCurrent ? "#46e342" : "#3598fa"
            anchors.left: itemRectIcon.left
            anchors.leftMargin: 50
        }

        Text {
            id: childRectIndicator
            anchors.left: interfaceName.left
            anchors.leftMargin: 60
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
