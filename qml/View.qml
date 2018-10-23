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

        onInterfaceSetActiveProperty: {
            projectPanel.devicePanel.devicePropertyPanel.setActiveInterfacePanelType(ioType, ioIndex)
        }
        onAddDeviceSuccesfull: {
            projectPanel.devicePanel.devicePropertyPanel.deviceAdded(devType, devKeyProperty, devValueProperty)
        }
        onDevSetActiveDeviceProperty: {
            projectPanel.devicePanel.devicePropertyPanel.setActiveDevicePanelType(devType, devIndex)
        }
        onInterfaceReadyProperties: {
            projectPanel.devicePanel.devicePropertyPanel.setInterfaceProperites(ioType, ioIndex, properties)
        }
//        onInterfaceAndDeviceListIsEmpty: {
//            projectPanel.devicePanel.devicePropertyPanel.setActiveLogoPanel()
//        }
        onDevReadyProperties: {
            projectPanel.devicePanel.devicePropertyPanel.setReadyProperties(devIndex, typeDev, keys, values)
        }
        onDevReadyPeriodicData: {
            projectPanel.devicePanel.devicePropertyPanel.setReadyPeriodicData(devIndex, typeDev, keys, values)
        }
        onDevConnected: {
            projectPanel.devicePanel.devicePropertyPanel.setDevConnected(devIndex, typeDev)
        }
        onDevReady: {
            projectPanel.devicePanel.devicePropertyPanel.setDevReady(devIndex, typeDev)
        }
        onDevDisconnected: {
            projectPanel.devicePanel.devicePropertyPanel.setDevDisconnected(devIndex, typeDev)
        }
//        onDevWrongTypeIncorrect: {
//            projectPanel.devicePanel.devicePropertyPanel.devShowTypeIncorrect(typeDev, devNameId)
//        }
        onAddConnectionFail: {
            projectPanel.devicePanel.devicePropertyPanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanel.devicePanel.devicePropertyPanel.showDeviceAddError(devName, errorMessage)
        }
        onDevShowMessage: {
            projectPanel.devicePanel.devicePropertyPanel.setDevShowMessage(typeDev, messageHeader, message)
        }
        onDevCustomCommandExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, devIndex, keys, args, ackMessageIsVisible)
        }
        onDevUpdateLogMessage: {
            projectPanel.devicePanel.devicePropertyPanel.addDeviceLog(devIndex, codeMessage, message)
        }
        onDevReadyCheckCommand: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertySerialPort.addDeviceDialog.setResultCheckDevice(devTypeName, devId, devSn, result)
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
                StartPanel {
                    id:projectPanel
                    anchors.top: upBar.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom

                    devicePanel.onAddNewConnection: {
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
