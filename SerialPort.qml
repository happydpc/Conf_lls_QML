import QtQuick 2.4

import ConnectionFactory 0.0

SerialPortForm {
    x: width
    y: height

    signal onCloseButtonEvent()
    signal onAcceptButtonEvent()

    ConnectionFactory {
        id:connectionFactory
    }

    onOpened: {
        updatePortList()
    }

    portList.onCurrentIndexChanged: {
        console.log("portList index changed")
    }

    buttonAccept.onClicked: {
        console.log("button Accept clicked")
        onAcceptButtonEvent()
        //        connectionFactory.addConnection()
    }
    buttonClose.onClicked: {
        console.log("button Close clicked")
        onCloseButtonEvent()
    }

    buttonUpdate.onClicked: {
        console.log("button update clicked")
        updatePortList()
    }


    function updatePortList() {
        console.log("Opened")
        var interfaceList = connectionFactory.getAvailableInterfacesToSerialPort()
        console.log("SerialPorts: " + interfaceList);

        portList.model.clear()
        baudRateList.model.clear()

        for(var it = 0; it<interfaceList.length; it++) {
            portList.model.append({text: interfaceList[it]})
        }
        portList.currentIndex = 0

        if(interfaceList.length > 0) {
            baudRateList.model.append({text: "4800"})
            baudRateList.model.append({text: "9600"})
            baudRateList.model.append({text: "19200"})
            baudRateList.model.append({text: "38400"})
            baudRateList.model.append({text: "115200"})
            baudRateList.model.append({text: "256000"})
        }
        baudRateList.currentIndex = 0;
    }
}
