import QtQuick 2.4
import QtQuick.Controls 2.2

TabButton {
    id:tabButtonUp
    property string name: name
    property int textLine: 1
    property int widthBody: 100
    property bool useIcon: false
    property string iconCode: ""
    width: widthBody
    height: 35
    background: Rectangle {
        height: 35
        width: widthBody
        radius: 25
        color: tabButtonUp.checked ? "#a3ff7b" : "#ffffff"
        border.color: "#e9eff4"
        border.width: 2
        Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            color: useIcon ? "transparent" : "#3598fa"
            width: 16
            height: 16
            Text {
                text: useIcon ? (iconCode) : ""
                color: "#3598fa"
                visible: useIcon
                font { family: "customFont";}
                font.pointSize: 14
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: textLine === 1 ? 10 : 3
            anchors.leftMargin: 40
            color: tabButtonUp.checked ? "black" : "#3598fa"
            font.pointSize: 8
            text: qsTr(name)
        }
    }
}
