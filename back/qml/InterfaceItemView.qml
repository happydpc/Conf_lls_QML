import QtQuick 2.0

Row{
    id: itemView

    signal eventClickLeft()
    signal eventClickRight();

    Rectangle {
        id: itemRectRoot
        width: 10
        height: 20

        Image {
            id:itemRectIcon
            anchors.left: itemRectRoot.left
            anchors.leftMargin: 5
            width: 24
            height: 24
            source: modelData.isCurrent ? "/new/icons/images/icon/cables_selected.png" : "/new/icons/images/icon/cables_no_selected.png"
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
        Rectangle {
            id: childRectIndicator
            width: 16
            height: 16
            anchors.left: interfaceName.left
            anchors.leftMargin: 60
            color: (modelData.hasChild) ? ("#a7b6c6") : ("transparent")
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
