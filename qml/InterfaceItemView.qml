import QtQuick 2.0

Row{
    id: itemView

    signal eventClickLeft()
    signal eventClickRight();

    Rectangle {
        id: itemRectRoot
        width: 10
        height: 10

        Rectangle {
            id:itemRectIcon
            anchors.left: itemRectRoot.left
            anchors.leftMargin: 5
            width: 16
            height: 16
            color: "#3598fa"
        }
        MouseArea{
            id:aread
            height: 20
            width: 100
            onClicked: {
                if(modelData.hasChild) {
                    modelData.isOpen = !modelData.isOpen;
                }
                modelData.isCurrent = true
                if (mouse.button === Qt.LeftButton) {
                    eventClickLeft()
                } else {
                    eventClickRight
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
