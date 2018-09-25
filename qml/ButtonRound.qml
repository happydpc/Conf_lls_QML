import QtQuick 2.4
import QtQuick.Controls 2.2

Button {
    id:button
    property string name: name
    property int textLine: 1
    property int widthBody: 100
    property bool textIsCenter: false
    property bool useIcon: false
    property string iconCode: ""
    width: widthBody
    height: textLine=== 1 ? 35 : 60

    background: Rectangle {
        height: textLine=== 1 ? 35 : 50
        width: widthBody
        radius: 25
        color: enabled ? (button.pressed ? "#a3ff7b" : "#ffffff") : "#cfcfcf"
        border.color: enabled ? ("#e9eff4") : ("#cfcfcf")
        border.width: 2
        Rectangle {
            id:rectIcon
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
            }
        }
        Text {
            anchors.left: textIsCenter!=true ? (rectIcon.right) : null
            anchors.leftMargin: textIsCenter!=true ? (rectIcon.width /2) : null
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: textIsCenter==true ? parent.horizontalCenter : null
            color: button.pressed ? "black" : "#3598fa"
            font.pointSize: 8
            text: qsTr(name)
        }
    }

    FontLoader { id: customFont; source: "qrc:/awesome_900.otf" }
}
