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
        color: "#ffffff"
        anchors.top: parent.top
        anchors.topMargin: devicePanel.height - 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        // stack for switch mode - device/SerialPort/startScreen
        StackView {
            id: projectStack
            height: parent.height
            width: parent.width
            initialItem: projectStartSceen
        }
    }
}
