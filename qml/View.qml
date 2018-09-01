import QtQuick 2.9
import QtQuick.Controls 2.4

import viewController 0.0

Item {
    id: root

    ViewController {
        id: viewController
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

//    ViewMain {
//        id: viewMain
////        onReadyCreateNewConnections: {
////            console.log("onReadyCreateNewConnections -y" + connecionsCountTypes);
////            for(var i=0; i<connecionsCountTypes; i++) {
////                console.log("connecionsCountTypes " + i + connection.getAvailableListInterfaceOfType(i))
////                serialPort.setListInterfaces(connection.getAvailableListInterfaceOfType(i))
////            }
////            serialPort.open()
////        }
////        // тут есть коннект
////        onConnectionOpened: {
////            console.log("onConnectionOpened: " + nameInterface + " " + subName)
////            serialPort.close()
////            projectPanels.openDeviceProject()
////            projectPanels.addInterface(subName)

////            //            projectPanels.addDevice("Test1")
////        }
//    }

    SerialPort {
        id:serialPort
        onAcceptConnectReady: {
            var res = viewController.addConnectionSerialPort(name, baudrate)
            console.log("addConnectionSerialPort=" + res)
            if(res) {
                close()
                projectPanels.openDeviceProject()
//                viewMain.openProject()
            }
        }
        onAbortConnectButton: {
            close()
        }
        Component.onCompleted: {
            visible = false
        }
    }

}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
