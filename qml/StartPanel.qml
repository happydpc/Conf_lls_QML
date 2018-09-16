import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    id: viewForm

    property alias devicePanel : devicePanel

    Rectangle {
        id: rootViewPanel
        color: "transparent"
        anchors.fill: parent

        // stack for switch mode - device/SerialPort/startScreen
        StackView {
            id: projectStack
            anchors.fill: parent
            initialItem: logoPanel

            LogoPanel {
                id: logoPanel
                anchors.fill: parent
            }
            DevicePanel {
                id: devicePanel
                anchors.fill: parent
                visible: false
            }
        }
        Component.onCompleted: {
            timerLogo.start()
        }
    }

    Timer {
        id: timerLogo
        interval: 100 //1000
        running: false
        repeat: false
        onTriggered: {
            projectStack.push(devicePanel)
        }
    }
}
