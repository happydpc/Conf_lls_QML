import QtQuick 2.9
import QtQuick.Controls 2.4

import viewController 0.0

Rectangle {
    id: devicePanel
    anchors.fill: parent

    property alias  devicePropertyPanel: devicePropertyPanel

    Rectangle {
        id: interfaceTree
        width: 220
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        height: parent.height / 2
//        border.color: "#ffffff"
                color: "transparent"
        ListView {
            id: listInterfaceView
            anchors.fill: interfaceTree
            spacing: 20
            clip: true
            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }
            model: programmModel.tree
            delegate: InterfaceItemView {
                onEventClickLeft: {
                    console.log("event left click")
                    devicePropertieslistModel1.push(devPropertyProgressTmk24)
                    devPropertyProgressTmk24.setNoReady()
                    viewController.setChangedIndexDevice(model.index)
                }
                onEventClickRight: {
                    console.log("event right click")
                    dialogRemoveDevice.open()
                }
            }
        }
    }
    Rectangle {
        id:spacerList
        anchors.top: interfaceTree.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: interfaceTree.right
        width: interfaceTree.width
        height: 2
        color: "#f0f3f6"
    }
    DevicePropertyPanel {
        id: devicePropertyPanel
        visible: true
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: interfaceTree.right
        anchors.right: parent.right
    }
}
