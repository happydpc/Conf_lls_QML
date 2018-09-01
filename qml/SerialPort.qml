import QtQuick 2.4
import QtQuick.Dialogs 1.3
import QtQuick 2.2

SerialPortForm {
    x: width
    y: height

    signal acceptConnectReady(var name, var baudrate)
    signal abortConnectButton()

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
        baudRateList.currentIndex = 0;
    }


    //    buttonUpdate.onClicked: {
    //        console.log("button update clicked")
    //        updatePortList()
    //    }

    //    MessageDialog {
    //        id: messageDialog
    //        title: "Ошибка открытия порта"
    //        text: "Проверьте доступность интерфейса\nПорт не удалось открыть"
    //        onAccepted: {
    //            close()
    //        }
    //    }

    //    function updatePortList() {
    //        console.log("Opened")
    //        var interfaceList = connectionFactory.getAvailableInterfacesToSerialPort()
    //        console.log("SerialPorts: " + interfaceList);

    //        portList.model.clear()
    //        baudRateList.model.clear()

    //        for(var it = 0; it<interfaceList.length; it++) {
    //            portList.model.append({text: interfaceList[it]})
    //        }
    //        portList.currentIndex = 0

    //        if(interfaceList.length > 0) {
    //            baudRateList.model.append({text: "4800"})
    //            baudRateList.model.append({text: "9600"})
    //            baudRateList.model.append({text: "19200"})
    //            baudRateList.model.append({text: "38400"})
    //            baudRateList.model.append({text: "115200"})
    //            baudRateList.model.append({text: "256000"})
    //        }
    //        baudRateList.currentIndex = 0;
    //        updated(interfaceList)
    //    }

    //    function closePort(name) {

    //    }
}
