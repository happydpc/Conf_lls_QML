import QtQuick 2.4

Column{
    spacing: 20
    Repeater{
        model: modelData.childItems

        delegate: Row {
            id: deviceTreeView

            Rectangle {
                id:rectBase
                width: 150
                height: 20

                MouseArea {
                    id:area
                    Rectangle {
                        anchors.fill: rectBase
                        color: "orange"
                    }
                    anchors.fill: parent
                    onClicked: {
                        console.log("MouseArea deviceTree clicked")
                        modelData.isCurrent = true
                    }
                }

                Rectangle {
                    id:iconRect
                    anchors.left: rectBase.left
                    anchors.leftMargin: 20
                    width: 16
                    height: 16
                    color: "#58fce4"
                }
                Text {
                    anchors.left: iconRect.right
                    anchors.leftMargin: 20
                    color: modelData.isCurrent === true ? "#46e342" : "#3598fa"
                    text: modelData.content
                }
            }
            Column{
                id:column
                spacing: 20
            }
        }
    }
}
