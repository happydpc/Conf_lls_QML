import QtQuick 2.4
import QtQuick.Controls 2.2

Button {
    id:button
    property string name: name
    property int textLine: 1
    property int widthBody: 100
    width: widthBody
    height: textLine=== 1 ? 35 : 60
    background: Rectangle {
        height: textLine=== 1 ? 35 : 50
        width: widthBody
        radius: 25
        color: button.pressed ? "#a3ff7b" : "#ffffff"
        border.color: "#e9eff4"
        border.width: 2
        Rectangle {
            id:rectIcon
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            color: "#3598fa"
            width: 16
            height: 16
        }
        Text {
            anchors.left: rectIcon.right
            anchors.leftMargin: rectIcon.width /2
            anchors.verticalCenter: parent.verticalCenter
            color: button.pressed ? "black" : "#3598fa"
            font.pointSize: 8
            text: qsTr(name)
        }
    }
}
