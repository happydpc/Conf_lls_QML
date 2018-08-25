import QtQuick 2.9
import QtQuick.Controls 2.4

import Connection 0.0

Item {
    id: root

    ProjectPanels {
        height: parent.height
        width: parent.width
        id:projectPanels
    }

    MainMenuBar {
        id:mainMenuBar
        onAddNewConnection: {
            console.log("onAddNewConnection -e")
            connection.addConnectionRequest()
        }
        onCloseProject: {
        }
        onExitFull: {
            Qt.quit()
        }
    }

    Connection {
        id:connection
        onReadyCreateNewConnections: {
            console.log("onReadyCreateNewConnections -y" + connecionsCountTypes);
            for(var i=0; i<connecionsCountTypes; i++) {
                console.log("connecionsCountTypes " + i + connection.getAvailableListInterfaceOfType(i))
                serialPort.setListInterfaces(connection.getAvailableListInterfaceOfType(i))
            }
            serialPort.open()
        }
        // тут есть коннект
        onConnectionOpened: {
            console.log("onConnectionOpened: " + nameInterface + " " + subName)
            serialPort.close()
            projectPanels.openDeviceProject()
            projectPanels.addInterface(subName)

            projectPanels.addDevice("Test1")
            projectPanels.addDevice("Test1")
            projectPanels.addDevice("Test1")
            projectPanels.addDevice("Test1")
            projectPanels.addDevice("Test1")
        }
    }

    SerialPort {
        id:serialPort
        onAcceptConnectReady: {
            connection.addConnection("SerialPort", nameInerface, arg)
        }
        onAbortConnectButton: {
            serialPort.close()
        }
        Component.onCompleted: {
            serialPort.visible = false
        }
    }

}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
