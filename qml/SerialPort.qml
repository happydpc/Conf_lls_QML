import QtQuick 2.4
import QtQuick.Dialogs 1.3
import QtQuick 2.2

SerialPortForm {
    x: width
    y: height

    modal: true
    property int anyPrope: 0

    signal acceptConnectReady(var name, var baudrate)
    signal abortConnectButton()

    Component.onCompleted: {
        buttonClose.useIcon = true
        buttonClose.iconCode = "\uf00d  "
        buttonAccept.useIcon = true
        buttonAccept.iconCode = "\uF1E6  "
        buttonUpdate.useIcon = true
        buttonUpdate.iconCode = "\uF0FE  "
    }

    buttonAccept.onClicked: {
        acceptConnectReady(portList.currentText, baudRateList.currentText)
    }
    buttonClose.onClicked: {
        console.log("button Close clicked")
        abortConnectButton()
    }

    function setListInterfaces(interfaceList) {
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
        baudRateList.currentIndex = 2; // 19200 default
    }
}
