import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    width: 1100
    height: 800
    id: viewForm

    property alias devicePanel: devicePanel

    function openDeviceProject() {
        projectStack.push(devicePanel)
    }
    function openStartScreen() {
        projectStack.pop()
    }

    StartScreen {
        id: projectStartSceen
        visible: false
    }

    DevicePanels {
        id: devicePanel
        visible: false
    }

    Rectangle {
        id: vewRootForm
        color: "#e4dbdb"
        anchors.top: parent.top
        anchors.topMargin: mainMenuBar.height - 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            id: statusBarRecangle
            height: 5//30
            color: "#dfe1e9"
            visible: false
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

        // stack for switch mode - device/SerialPort/startScreen
        StackView {
            id: projectStack
            height: parent.height - statusBarRecangle.height
            width: parent.width
            initialItem: projectStartSceen
        }
    }
}
