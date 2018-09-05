import QtQuick 2.9
import QtQuick.Controls 2.4

import viewController 0.0

Item {
    id: root

    ViewController {
        id: viewController
        onAddDeviceSignal: {
            projectPanels.addDevice(name)
        }
        onAddInterfaceSignal: {
            projectPanels.openDeviceProject()
            projectPanels.addInterface(name)
        }
        onUpdatePropertiesSerialPort_Signal: {
            projectPanels.devicePanel.setPropertyToSerialPort(data)
        }
        onUpdatePropertiesDevTmk24_Signal: {
//            projectPanels.devicePanel.devPropertyLlsTMK24.setDevProperty(data)
        }
        onUpdatePropertiesDevTmk13_Signal: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setDevProperty(data)
        }
        onUpdateDataDevTmk13_Signal: {
            projectPanels.devicePanel.devPropertyLlsTMK24.setUpdateCurrentValues(data)
        }
        onUpdateDataDevTmk24_Signal: {
//            projectPanels.devicePanel.devPropertyLlsTMK24.setUpdateCurrentValues(data)
        }
        onUpdateDevTmk13_NoReady_Signal: {
//            projectPanels.devicePanel.devPropertyLlsTMK24.setNoActive()
        }
        onUpdateDevTmk24_NoReady_Signal: {
//            projectPanels.devicePanel.devPropertyLlsTMK24.setNoActive()
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
