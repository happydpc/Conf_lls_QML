import QtQuick 2.9
import QtQuick.Controls 2.4

import "qrc:/qml/devices"
import "qrc:/qml/devTree"
import "qrc:/qml/interfaces"
import "qrc:/qml/miscElems"
import "qrc:/qml/projectPanel"

Item {
    id: root

//    void addIoSucces(QString ioType, QStringList keyProperty, QStringList valueProperty);
//    void removeIoSucces(int ioIndex);
//    void onAddDevSucces(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
//    void onRemoveDeviceSucces(int ioIndex, int devIndex);
//    void onIoTreeIsEmpty();
//    void onDevSetActiveDeviceProperty(QString devType, int ioIndex, int devIndex);
//    void onIoReadyProperties(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
//    void onDevReadyProperties(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
//    void onDevReadyPeriodicData(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
//    void onDevConnected(int ioIndex, int devIndex, QString typeDev);
//    void onDevReady(int ioIndex, int devIndex, QString typeDev);
//    void onDevDisconnected(int ioIndex, int devIndex, QString typeDev);
//    void onAddIoFail();
//    void onAddDeviceFail(QString devName, QString errorMessage);
//    void onDevCommandExecuted(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList args);
//    void onDevUpdateLogMessage(int ioIndex, int devIndex, QString codeMessage, QString message);
//    void onDevReadyCheckCommand(int ioIndex, QString devTypeName, QString devId, QString devSn, QString result);
//    void devUpdateLogMessage(int ioIndex, int devIndex, int codeMessage, QString message);
//    void devReadyCheckCommand(int ioIndex, QString devTypeName, QString devId, QString devSn, bool result);
//    void ioSetActiveProperty(int ioIndex, QString ioType);
//    void ioAndDeviceListIsEmpty();
//    void isAvailableNewVersion(QString downloadUrl);

    Connections {
        target: controller

        onAddIoSucces: {
            projectPanel.devicePropertyPanel.intefaceAdded(ioType, keyProperty, valueProperty)
        }
        onRemoveIoSucces: {
            projectPanel.devicePropertyPanel.intefaceDeleted(ioIndex)
        }
        onAddDevSucces: {
            projectPanel.devicePropertyPanel.deviceAdded(ioIndex, devType, devKeyProperty, devValueProperty)
        }
        onRemoveDeviceSucces: {
            projectPanel.devicePropertyPanel.deviceDeleted(ioIndex, devIndex)
        }
        onIoTreeIsEmpty: {
            projectPanel.devicePropertyPanel.setActiveLogoPanel()
        }
        onDevSetActiveDeviceProperty: {
            projectPanel.devicePropertyPanel.setActiveDevicePanelType(devType, ioIndex, devIndex)
        }
        onIoReadyProperties: {
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
        onAddIoFail: {
            projectPanel.devicePropertyPanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanel.devicePropertyPanel.showDeviceAddError(devName, errorMessage)
        }
        onDevCommandExecuted: {
            try {                
                projectPanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, ioIndex, devIndex, keys, args)
            } catch (error) {
                console.log ("Error loading QML : ")
                for (var i = 0; i < error.qmlErrors.length; i++) {
                    console.log("lineNumber: " + error.qmlErrors[i].lineNumber)
                    console.log("columnNumber: " + error.qmlErrors[i].columnNumber)
                    console.log("fileName: " + error.qmlErrors[i].fileName)
                    console.log("message: " + error.qmlErrors[i].message)
                }
            }
        }
        onDevUpdateLogMessage: {
            projectPanel.devicePropertyPanel.addDeviceLog(ioIndex, devIndex, codeMessage, message)
        }
        onDevReadyCheckCommand: {
            projectPanel.devicePropertyPanel.intefaceSetResultCheckDevice(ioIndex, devTypeName, devId, devSn, result)
        }
        onRemoveAllContent: {
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
                    //                    Image {
                    //                        anchors.left: parent.left
                    //                        anchors.top: parent.top
                    //                        anchors.topMargin: -65
                    //                        source: "logo.png"
                    //                        width: 256
                    //                        height: 160
                    //                        visible: false
                    //                    }
                }

                DevListPanel {
                    id:projectPanel
                    anchors.top: upBar.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    onAddNewConnection: {
                        var list = controller.getAvailableIoToAdd("serial")
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
                        var res = controller.addIo("serial", name, keyList, paramList)
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
}
