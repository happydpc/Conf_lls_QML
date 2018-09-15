import QtQuick 2.9
import QtQuick.Controls 2.4

import viewController 0.0

Item {
    id: root

    ViewController {
        id: viewController

        onRemakeInterfaceTree: {
//            projectPanel.devicePanel.remakeInterfaceList(list, status)
        }
        onRemakeDeviceTree: {
//            projectPanel.devicePanel.remakeDeviceList(list, status)
        }
        onChangeDeviceTreeStatus: {
//            projectPanel.devicePanel.updateDeviceListStatus(index, status)
        }
        onChangeInterfaceTreeStatus: {
//            projectPanel.devicePanel.updateIntefaceListStatus(index, status)
        }

        onUpdatePropertiesSerialPort: {
            projectPanel.devicePanel.devicePropertyPanel.setActivePanelType("SerialPort")
//            projectPanel.devicePanel.setPropertyToSerialPort(properties)
        }
        onDevReadyPropertiesTmk4ux: {
//            projectPanel.devicePanel.devPropertyProgressTmk4ux.setDevProperty(data)
        }
        onDevReadyPropertiesTmk24: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.setDevProperty(data)
        }
        onDevReadyOtherDataTmk4ux: {
//            projectPanel.devicePanel.devPropertyProgressTmk4ux.setUpdateCurrentValues(data)
        }
        onDevReadyOtherDataTmk24: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.setUpdateCurrentValues(data)
        }
        onDevFullReadyTmk4ux: {}
        onDevFullReadyTmk24: {}
        onDevDisconnectedTmk4ux: {
//            projectPanel.devicePanel.devPropertyProgressTmk4ux.setNoReady()
        }
        onDevDisconnectedTmk24: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.setNoReady()
        }
        onDevUpdatePasswordIncorrect: {
//            projectPanel.devicePanel.devShowPasswordIncorrect(devNameId)
        }
        onDevUpdateTypeDevIncorrect: {
//            projectPanel.devicePanel.devShowTypeIncorrect(devNameId)
        }
        onAddConnectionFail: {
//            projectPanel.devicePanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
//            projectPanel.devicePanel.dialogAddDeviceFail.open()
        }
        onDevUpdateWriteScaleMeasureExecuted: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.messageMinMaxWriteOk.open()
        }
        onDevUpdateWriteSettingExecuted: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.messageWriteSettingsOk.open()
        }
        onDevUpdateReadSettingExecuted: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
//            projectPanel.devicePanel.devPropertyProgressTmk24.messageReadSettingsOk.open()
        }
        onDevUpdateReadSettingWithoutRequest: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
        }
        onDevUpdateReadErrorsExecuted: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.readErrors(devNameId, errors)
//            projectPanel.devicePanel.devPropertyProgressTmk24.messageReadErrorsOk.open()
        }
        onDevUpdateLogMessage: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.addLogMessage(codeMessage, message)
        }
        onDevUpdateReadTarTable: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.readTarTable(table)
        }
        onDevUpdateWriteTarTableExecuted: {
//            projectPanel.devicePanel.devPropertyProgressTmk24.messageReadTarTableOk.open()
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
    }

    StartPanel {
        id:projectPanel
        anchors.top: upBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    SerialPort {
        id:serialPort
        onAcceptConnectReady: {
            var res = viewController.addConnectionSerialPort(name, baudrate)
            console.log("addConnectionSerialPort=" + res)
            if(res) {
                close()
                projectPanel.openDeviceProject()
            }
        }
        onAbortConnectButton: {
            close()
        }
    }
}

//    MainMenuBar {
//        id:mainMenuBar
//        onAddNewConnection: {
//            var list = viewController.getAvailableNameToSerialPort()
//            console.log("Available interface-" + list)
//            serialPort.setListInterfaces(list)
//            serialPort.open()
//        }
//        onCloseProject: {
//        }
//        onExitFull: {
//            Qt.quit()
//        }
//    }

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
