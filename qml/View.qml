import QtQuick 2.9
import QtQuick.Controls 2.4

import "qrc:/qml/devices"
import "qrc:/qml/devTree"
import "qrc:/qml/interfaces"
import "qrc:/qml/miscElems"
import "qrc:/qml/projectPanel"

Item {
    id: root
    Connections {
        target: viewController

        onAddInterfaceSuccesfull: {
            projectPanel.devicePropertyPanel.intefaceAdded(ioType, keyProperty, valueProperty)
        }
        onDeleteInterfaceSuccesfull: {
            projectPanel.devicePropertyPanel.intefaceDeleted(ioIndex)
        }
        onInterfaceSetActiveProperty: {
            projectPanel.devicePropertyPanel.setActiveInterfacePanelType(ioType, ioIndex)
        }
        onAddDeviceSuccesfull: {
            projectPanel.devicePropertyPanel.deviceAdded(devType, devKeyProperty, devValueProperty)
        }
        onDeleteDeviceSuccesfull: {
            projectPanel.devicePropertyPanel.deviceAdded(devIndex)
        }
        onInterfaceAndDeviceListIsEmpty: {
            projectPanel.devicePropertyPanel.setActiveLogoPanel()
        }
        onDevSetActiveDeviceProperty: {
            projectPanel.devicePropertyPanel.setActiveDevicePanelType(devType, devIndex)
        }
        onInterfaceReadyProperties: {
            projectPanel.devicePropertyPanel.setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty)
        }
        onDevReadyProperties: {
            projectPanel.devicePropertyPanel.setReadyProperties(devIndex, typeDev, keys, values)
        }
        onDevReadyPeriodicData: {
            projectPanel.devicePropertyPanel.setReadyPeriodicData(devIndex, typeDev, keys, values)
        }
        onDevConnected: {
            projectPanel.devicePropertyPanel.setDevConnected(devIndex, typeDev)
        }
        onDevReady: {
            projectPanel.devicePropertyPanel.setDevReady(devIndex, typeDev)
        }
        onDevDisconnected: {
            projectPanel.devicePropertyPanel.setDevDisconnected(devIndex, typeDev)
        }
        onAddConnectionFail: {
            projectPanel.devicePropertyPanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanel.devicePropertyPanel.showDeviceAddError(devName, errorMessage)
        }
        onDevShowMessage: {
            projectPanel.devicePropertyPanel.setDevShowMessage(typeDev, messageHeader, message)
        }
        onDevCustomCommandExecuted: {
            projectPanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, devIndex, keys, args, ackMessageIsVisible)
        }
        onDevUpdateLogMessage: {
            projectPanel.devicePropertyPanel.addDeviceLog(devIndex, codeMessage, message)
        }
        onDevReadyCheckCommand: {
            projectPanel.devicePropertyPanel.intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result)
        }
    }

    Rectangle {
        id: rootPanel
        color: "#e4dbdb"
        anchors.fill: parent

        StackView {
            id: projectStack
            anchors.fill: parent
            initialItem: projectStartSceen

            ProjectStartScreen {
                id: projectStartSceen
            }

            Item {
                id: projectDeviceScreen
                Rectangle {
                    id:upBar
                    color: "#404558"
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 50
                    width: parent.width
                    Image {
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: -65
                        source: "logo.png"
                        width: 256
                        height: 160
                        visible: false
                    }
                }

                DevListPanel {
                    id:projectPanel
                    anchors.top: upBar.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    onAddNewConnection: {
                        var list = viewController.getInterfaceAvailableToAdd("serial")
                        console.log("Available interface-" + list)
                        addInterface.setListInterfaces(list)
                        addInterface.open()
                    }
                }
                AddSerialPort {
                    visible: false
                    id:addInterface
                    onAcceptConnectReady: {
                        var paramList = []
                        var keyList = []
                        keyList.push("baudrate")
                        paramList.push(baudrate)
                        var res = viewController.addConnection("serial", name, keyList, paramList)
                        console.log("addConnectionaddInterface=" + res)
                        if(res) {
                            close()
                        }
                    }
                    onAbortConnectButton: {
                        close()
                    }
                }
            }
        }
    }
    Timer {
        id: timerStartScreen
        interval: 100
        running: true
        repeat: false
        onTriggered: {
            projectStack.push(projectDeviceScreen)
        }
    }
}
