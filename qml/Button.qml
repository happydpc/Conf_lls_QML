import QtQuick 2.4
import QtQuick.Controls 2.2

Button {
    id:standardButton
    property string name: name
    property int textLine: 1
    property int widthBody: 100
    width: widthBody
    height: 35
    background: Rectangle {
        height: 35
        width: widthBody
        radius: 25
        color: standardButton.checked ? "#a3ff7b" : "#ffffff"
        border.color: "#e9eff4"
        border.width: 2
        Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.top: parent.top
            anchors.topMargin: 10
            color: "#3598fa"
            width: 16
            height: 16
        }
        Text {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: textLine === 1 ? 10 : 3
            anchors.leftMargin: 40
            color: standardButton.checked ? "black" : "#3598fa"
            font.pointSize: 8
            text: qsTr(name)
        }
    }
}
