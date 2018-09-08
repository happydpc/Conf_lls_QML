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

        onUpdatePropertiesSerialPort: {
            projectPanels.devicePanel.setPropertyToSerialPort(properties)
        }
        onDevReadyPropertiesTmk13: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setDevProperty(data)
        } 
        onDevReadyPropertiesTmk24: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setDevProperty(data)
        }
        onDevReadyOtherDataTmk13: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setUpdateCurrentValues(data)
        }
        onDevReadyOtherDataTmk24: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setUpdateCurrentValues(data)
        }
        onDevFullReadyTmk13: {}
        onDevFullReadyTmk24: {}
        onDevDisconnectedTmk13: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setNoActive()
        }
        onDevDisconnectedTmk24: {

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
    }

    ProjectPanels {
        height: parent.height
        width: parent.width
        id:projectPanels
    }

    MainMenuBar {
        id:mainMenuBar
        onAddNewConnection: {
            var list = viewController.getAvailableNameToSerialPort()
            console.log("Available interface-" + list)
            serialPort.setListInterfaces(list)
            serialPort.open()
        }
        onCloseProject: {
        }
        onExitFull: {
            Qt.quit()
        }
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


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
