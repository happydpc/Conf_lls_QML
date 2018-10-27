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
            projectPanel.devicePropertyPanel.deviceAdded(ioIndex, devType, devKeyProperty, devValueProperty)
        }
        onDeleteDeviceSuccesfull: {
            projectPanel.devicePropertyPanel.deviceDeleted(ioIndex, devIndex)
        }
        onInterfaceAndDeviceListIsEmpty: {
            projectPanel.devicePropertyPanel.setActiveLogoPanel()
        }
        onDevSetActiveDeviceProperty: {
            projectPanel.devicePropertyPanel.setActiveDevicePanelType(devType, ioIndex, devIndex)
        }
        onInterfaceReadyProperties: {
            projectPanel.devicePropertyPanel.setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty)
        }
        onDevReadyProperties: {
            projectPanel.devicePropertyPanel.setDevReadyProperties(typeDev, ioIndex, devIndex, keys, values)
        }
        onDevReadyPeriodicData: {
            projectPanel.devicePropertyPanel.setReadyPeriodicData(typeDev, ioIndex, devIndex, keys, values)
        }
        onDevConnected: {
            projectPanel.devicePropertyPanel.setDevConnected(ioIndex, devIndex, typeDev)
        }
        onDevReady: {
            projectPanel.devicePropertyPanel.setDevReady(ioIndex, devIndex, typeDev)
        }
        onDevDisconnected: {
            projectPanel.devicePropertyPanel.setDevDisconnected(ioIndex, devIndex, typeDev)
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
        onDevCustomCommandExecuted: { // OK
            projectPanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, ioIndex, devIndex, keys, args, ackMessageIsVisible)
        }
        onDevUpdateLogMessage: {
            projectPanel.devicePropertyPanel.addDeviceLog(ioIndex, devIndex, codeMessage, message)
        }
        onDevReadyCheckCommand: {
            projectPanel.devicePropertyPanel.intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result)
        }
        onClearAllFrontEndItems: {
            projectPanel.devicePropertyPanel.setCrearAllItems()
        }
        onIsAvailableNewVersion: {
            projectPanel.devicePropertyPanel.updateVersionDialog.url = downloadUrl
            projectPanel.devicePropertyPanel.updateVersionDialog.open()
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
                    x: rootPanel.height / 5
                    y: rootPanel.width / 5
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
