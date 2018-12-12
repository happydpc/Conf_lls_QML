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
        target: controller

        onSignal_add_Io:{
            projectPanel.devicePropertyPanel.intefaceAdded(resultKey, resultValue)
        }
        onSignal_remove_Io:{}//(QVector<QString> resultKey, QVector<QString> resultValue);
        onSignal_add_dev_to_Io:{}//(QVector<QString> resultKey, QVector<QString> resultValue);
        onSignal_get_add_types:{}//(QVector<QString> resultKey, QVector<QString> resultValue);
        onSignal_remove_dev_of_Io:{}//(QVector<QString> resultKey, QVector<QString> resultValue);
        onSignal_exec_dev_command:{}//(QVector<QString> resultKey, QVector<QString> resultValue);


        onIoTreeIsEmpty: {
            projectPanel.devicePropertyPanel.setActiveLogoPanel()
        }

//        onRemoveIoSucces: {
//            projectPanel.devicePropertyPanel.intefaceDeleted(ioIndex)
//        }
//        onAddDevSucces: {
//            projectPanel.devicePropertyPanel.deviceAdded(ioIndex, devType, devKeyProperty, devValueProperty)
//        }
//        onRemoveDeviceSucces: {
//            projectPanel.devicePropertyPanel.deviceDeleted(ioIndex, devIndex)
//        }
//        onDevSetActiveDeviceProperty: {
//            projectPanel.devicePropertyPanel.setActiveDevicePanelType(devType, ioIndex, devIndex)
//        }
//        onIoReadyProperties: {
//            projectPanel.devicePropertyPanel.setInterfaceProperites(ioType, ioIndex, keyProperty, valueProperty)
//        }
//        onDevReadyProperties: {
//            projectPanel.devicePropertyPanel.setDevReadyProperties(typeDev, ioIndex, devIndex, keys, values)
//        }
//        onDevReadyPeriodicData: {
//            projectPanel.devicePropertyPanel.setReadyPeriodicData(typeDev, ioIndex, devIndex, keys, values)
//        }
//        onDevConnected: {
//            projectPanel.devicePropertyPanel.setDevConnected(ioIndex, devIndex, typeDev)
//        }
//        onDevReady: {
//            projectPanel.devicePropertyPanel.setDevReady(ioIndex, devIndex, typeDev)
//        }
//        onDevDisconnected: {
//            projectPanel.devicePropertyPanel.setDevDisconnected(ioIndex, devIndex, typeDev)
//        }
//        onAddIoFail: {
//            projectPanel.devicePropertyPanel.dialogAddInterfaceFail.open()
//        }
//        onAddDeviceFail: {
//            projectPanel.devicePropertyPanel.showDeviceAddError(devName, errorMessage)
//        }
//        onDevCommandExecuted: {
//            try {
//                projectPanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, ioIndex, devIndex, keys, args)
//            } catch (error) {
//                console.log ("Error loading QML : ")
//                for (var i = 0; i < error.qmlErrors.length; i++) {
//                    console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
//                    console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
//                    console.log("fileName: " + error.qmlErrors[i].fileName)
//                    console.log("message: " + error.qmlErrors[i].message)
//                }
//            }
//        }
//        onDevUpdateLogMessage: {
//            projectPanel.devicePropertyPanel.addDeviceLog(ioIndex, devIndex, codeMessage, message)
//        }
//        onDevReadyCheckCommand: {
//            projectPanel.devicePropertyPanel.intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result)
//        }
//        onRemoveAllContent: {
//            projectPanel.devicePropertyPanel.setCrearAllItems()
//        }
//        onIsAvailableNewVersion: {
//            projectPanel.devicePropertyPanel.updateVersionDialog.url = downloadUrl
//            projectPanel.devicePropertyPanel.updateVersionDialog.open()
//        }
    }

    Rectangle {
        id: rootPanel
        color: "#e4dbdb"
        anchors.fill: parent

        StackView {
            id: projectStack
            anchors.fill: parent
            initialItem: projectDeviceScreen

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
                }
                DevListPanel {
                    id:projectPanel
                    anchors.top: upBar.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    onAddNewConnection: {
                        controller.onSignal_get_availableIo.connect(function func(resultKey, resultValue) {
                            controller.onSignal_get_availableIo.disconnect(func);
                            addInterface.setListInterfaces(resultValue)
                            addInterface.open()
                        });
                        controller.requestGetIoAddTypes("serial")
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
                        controller.onSignal_add_Io.connect(function func(resultKey, resultValue) {
                            controller.onSignal_get_availableIo.disconnect(func);
                            close()
                        });
                        controller.requestAddIo("serial", name, keyList, paramList)
                    }
                    onAbortConnectButton: {
                        close()
                    }
                }
            }
        }
    }
}
