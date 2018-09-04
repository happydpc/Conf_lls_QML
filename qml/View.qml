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
        onUpdateCurrentDataDevTmk24_Signal: {
            projectPanels.setCurrentDataToDeviceTmk24(data)
        }
        onUpdatePropertySerialPort_Signal: {
            projectPanels.setPropertyToSerialPort(data)
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
