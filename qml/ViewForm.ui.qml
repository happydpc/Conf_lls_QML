import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    width: 1100
    height: 800
    property alias statusBarRecangle: statusBarRecangle
    property alias projectStack: projectStack
    property alias projectDeviceScreen: projectDeviceScreen
    property alias projectStartSceen: projectStartSceen
    property alias statusBar: statusBar

    Rectangle {
        id: vewRootForm
        color: "#e4dbdb"
        anchors.top: parent.top
        anchors.topMargin: menuMain.height - 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            id: statusBarRecangle
            height: 30
            color: "#dfe1e9"
            radius: 0
            border.width: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Label {
                id: statusBar
                color: "#04203b"
                text: qsTr("Label")
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 15
            }
        }

        StackView {
            id: projectStack
            height: parent.height - statusBarRecangle.height
            width: parent.width
            initialItem: projectStartSceen

            ProjectMainStack {
                id: projectDeviceScreen
            }
            ProjectStartScreen {
                id: projectStartSceen
            }
        }
    }
}
