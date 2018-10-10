import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    id: root

    Connections {
        target: viewController

        onInterfaceSetActiveProperty: {
            projectPanel.devicePanel.devicePropertyPanel.setActiveInterfacePanelType(ioType)
        }
        onSetActiveDeviceProperty: {
            projectPanel.devicePanel.devicePropertyPanel.setActiveDevicePanelType(devType)
        }
        onInterfaceReadyProperties: {
            projectPanel.devicePanel.devicePropertyPanel.setInterfaceProperites(ioType, properties)
        }
        onInterfaceAndDeviceListIsEmpty: {}
        onDevReadyProperties: {
            projectPanel.devicePanel.devicePropertyPanel.setReadyProperties(typeDev, data)
        }
        onDevReadyPeriodicData: {
            projectPanel.devicePanel.devicePropertyPanel.setReadyPeriodicData(typeDev, data)
        }
        onDevDisconnected: {
            projectPanel.devicePanel.devicePropertyPanel.setDevDisconnected(typeDev)
        }
        onDevWrongTypeIncorrect: {
            projectPanel.devicePanel.devicePropertyPanel.devShowTypeIncorrect(typeDev, devNameId)
        }
        onAddConnectionFail: {
            projectPanel.devicePanel.devicePropertyPanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanel.devicePanel.devicePropertyPanel.dialogAddDeviceFail.open()
        }

        onDevShowMessage: {
            projectPanel.devicePanel.devicePropertyPanel.setDevShowMessage(typeDev, messageHeader, message)
        }

        onDevCustomCommandExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.setDevCustomCommandExecuted(typeDev, keys, args)
        }

        onDevUpdateLogMessage: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.addLogMessage(codeMessage, message)
        }
        onDevUpdateLogDeviceMessage: {
            projectPanel.devicePanel.devicePropertyPanel.addDeviceLog(typeDev, message)
        }

//        onDevUpdateWriteSettingExecuted: {
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageWriteSettingsOk.open()
//        }
//        onDevUpdateReadSettingExecuted: {
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadSettingsOk.open()
//        }
//        onDevUpdateReadSettingWithoutRequest: {
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
//        }
//        onDevUpdateReadErrorsExecuted: {
//        emit devUpdateReadErrorsExecuted(pDevFactory->getDeviceName(indexDev),
//                                         pDevFactory->getDeviceErrrors(indexDev));
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readErrors(devNameId, errors)
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadErrorsOk.open()
//        }
//        onDevUpdatePasswordIncorrect: {
//            projectPanel.devicePanel.devicePropertyPanel.devShowPasswordIncorrect(devType, devNameId)
//        }
//        onDevUpdateReadTarTable: {
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readTarTable(devCount)
//        }
//        onDevUpdateWriteTarTableExecuted: {
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadTarTableOk.message = result
//            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadTarTableOk.open()
//        }
//        onDevErrorOperation: {
//            projectPanel.devicePanel.messageOperationError.message = message
//            projectPanel.devicePanel.messageOperationError.open()
//        }

    }

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
            source: "/new/icons/images/logo/ico.png"
            width: 256
            height: 160
            visible: false //!!!
        }
    }

    StartPanel {
        id:projectPanel
        anchors.top: upBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        devicePanel.onAddNewConnection: {
            var list = viewController.getAvailableNameToSerialPort()
            console.log("Available interface-" + list)
            serialPort.setListInterfaces(list)
            serialPort.open()
        }
    }

    SerialPort {
        id:serialPort
        onAcceptConnectReady: {
            var res = viewController.addConnectionSerialPort(name, baudrate)
            console.log("addConnectionSerialPort=" + res)
            if(res) {
                close()
            }
        }
        onAbortConnectButton: {
            close()
        }
    }
}
