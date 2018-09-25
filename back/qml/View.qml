import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    id: root

    Connections {
        target: viewController

        onSetActivePropertySerialPort: {
            projectPanel.devicePanel.devicePropertyPanel.setActivePanelType("SerialPort")
        }
        onSetActivePropertyProgressTmk24: {
            projectPanel.devicePanel.devicePropertyPanel.setActivePanelType("PROGRESS TMK24")
        }
        onUpdatePropertiesSerialPort: {
            projectPanel.devicePanel.devicePropertyPanel.setActivePanelType("SerialPort")
            projectPanel.devicePanel.devicePropertyPanel.setPropertyToSerialPort(properties)
        }
        onInterfaceAndDeviceListIsEmpty: {
            projectPanel.devicePanel.devicePropertyPanel.setActivePanelType("Empty")
        }
        onDevReadyPropertiesTmk4ux: {
        }
        onDevReadyPropertiesTmk24: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.setDevProperty(data)
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.setReady()
        }
        onDevReadyOtherDataTmk4ux: {
        }
        onDevReadyOtherDataTmk24: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.setUpdateCurrentValues(data)
        }
        onDevFullReadyTmk4ux: {}
        onDevFullReadyTmk24: {}
        onDevDisconnectedTmk4ux: {}
        onDevDisconnectedTmk24: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.setNoReady()
        }
        onDevUpdatePasswordIncorrect: {
            projectPanel.devicePanel.devicePropertyPanel.devShowPasswordIncorrect(devType, devNameId)
        }
        onDevUpdateTypeDevIncorrect: {
            projectPanel.devicePanel.devicePropertyPanel.devShowTypeIncorrect(devNameId)
        }
        onAddConnectionFail: {
            projectPanel.devicePanel.devicePropertyPanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanel.devicePanel.devicePropertyPanel.dialogAddDeviceFail.open()
        }
        onDevUpdateWriteScaleMeasureExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageMinMaxWriteOk.open()
        }
        onDevUpdateWriteSettingExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageWriteSettingsOk.open()
        }
        onDevUpdateReadSettingExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadSettingsOk.open()
        }
        onDevUpdateReadSettingWithoutRequest: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
        }
        onDevUpdateReadErrorsExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readErrors(devNameId, errors)
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadErrorsOk.open()
        }
        onDevUpdateLogMessage: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.addLogMessage(codeMessage, message)
        }
        onDevUpdateReadTarTable: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.readTarTable(devCount)
        }
        onDevUpdateWriteTarTableExecuted: {
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadTarTableOk.message = result
            projectPanel.devicePanel.devicePropertyPanel.devPropertyProgressTmk24.messageReadTarTableOk.open()
        }
        onDevErrorOperation: {
            projectPanel.devicePanel.messageOperationError.message = message
            projectPanel.devicePanel.messageOperationError.open()
        }
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
        }
//        Image {
//            anchors.right: parent.right
//            anchors.rightMargin: 10
//            anchors.top: parent.top
//            source: "/new/icons/images/icon/user.png"
//            width: 48
//            height: 48
//        }
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
