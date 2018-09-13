import QtQuick 2.9
import QtQuick.Controls 2.4

import viewController 0.0

Item {
    id: root

    ViewController {
        id: viewController

        onRemakeInterfaceTree: {
            projectPanels.devicePanel.remakeInterfaceList(list, status)
        }
        onRemakeDeviceTree: {
            projectPanels.devicePanel.remakeDeviceList(list, status)
        }
        onChangeDeviceTreeStatus: {
            projectPanels.devicePanel.updateDeviceListStatus(index, status)
        }
        onChangeInterfaceTreeStatus: {
            projectPanels.devicePanel.updateIntefaceListStatus(index, status)
        }

        onUpdatePropertiesSerialPort: {
            projectPanels.devicePanel.setPropertyToSerialPort(properties)
        }
        onDevReadyPropertiesTmk4ux: {
            projectPanels.devicePanel.devPropertyProgressTmk4ux.setDevProperty(data)
        }
        onDevReadyPropertiesTmk24: {
            projectPanels.devicePanel.devPropertyProgressTmk24.setDevProperty(data)
        }
        onDevReadyOtherDataTmk4ux: {
            projectPanels.devicePanel.devPropertyProgressTmk4ux.setUpdateCurrentValues(data)
        }
        onDevReadyOtherDataTmk24: {
            projectPanels.devicePanel.devPropertyProgressTmk24.setUpdateCurrentValues(data)
        }
        onDevFullReadyTmk4ux: {}
        onDevFullReadyTmk24: {}
        onDevDisconnectedTmk4ux: {
            projectPanels.devicePanel.devPropertyProgressTmk4ux.setNoReady()
        }
        onDevDisconnectedTmk24: {
            projectPanels.devicePanel.devPropertyProgressTmk24.setNoReady()
        }
        onDevUpdatePasswordIncorrect: {
            projectPanels.devicePanel.devShowPasswordIncorrect(devNameId)
        }
        onDevUpdateTypeDevIncorrect: {
            projectPanels.devicePanel.devShowTypeIncorrect(devNameId)
        }
        onAddConnectionFail: {
            projectPanels.devicePanel.dialogAddInterfaceFail.open()
        }
        onAddDeviceFail: {
            projectPanels.devicePanel.dialogAddDeviceFail.open()
        }
        onDevUpdateWriteScaleMeasureExecuted: {
            projectPanels.devicePanel.devPropertyProgressTmk24.messageMinMaxWriteOk.open()
        }
        onDevUpdateWriteSettingExecuted: {
            projectPanels.devicePanel.devPropertyProgressTmk24.messageWriteSettingsOk.open()
        }
        onDevUpdateReadSettingExecuted: {
            projectPanels.devicePanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
            projectPanels.devicePanel.devPropertyProgressTmk24.messageReadSettingsOk.open()
        }
        onDevUpdateReadSettingWithoutRequest: {
            projectPanels.devicePanel.devPropertyProgressTmk24.readSettings(devNameId, key, settings)
        }
        onDevUpdateReadErrorsExecuted: {
            projectPanels.devicePanel.devPropertyProgressTmk24.readErrors(devNameId, errors)
            projectPanels.devicePanel.devPropertyProgressTmk24.messageReadErrorsOk.open()
        }
        onDevUpdateLogMessage: {
            projectPanels.devicePanel.devPropertyProgressTmk24.addLogMessage(codeMessage, message)
        }
        onDevUpdateReadTarTable: {
            projectPanels.devicePanel.devPropertyProgressTmk24.readTarTable(table)
        }
        onDevUpdateWriteTarTableExecuted: {
            projectPanels.devicePanel.devPropertyProgressTmk24.messageReadTarTableOk.open()
        }
        onDevErrorOperation: {
            projectPanels.devicePanel.messageOperationError.message = message
            projectPanels.devicePanel.messageOperationError.open()
        }
    }

    ProjectPanels {
        id:projectPanels
        height: parent.height
        width: parent.width
    }

    Rectangle {
        id:upBar
        color: "#404558"
        height: 50
        width: parent.width
    }


    SerialPort {
        id:serialPort
        onAcceptConnectReady: {
            var res = viewController.addConnectionSerialPort(name, baudrate)
            console.log("addConnectionSerialPort=" + res)
            if(res) {
                close()
                projectPanels.openDeviceProject()
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
