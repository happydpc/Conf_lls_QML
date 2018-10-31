import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "qrc:/qml/miscElems"

Popup {
    id: popup
    width: 250
    height: 280
    x: width
    y: height
    modal: true
    clip: true

    signal acceptConnectReady(var name, var baudrate)
    signal abortConnectButton()

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

    Rectangle {
        id: rectangle
        anchors.fill: parent
        Column {
            anchors.fill: parent
            spacing: 20
            Label {
                id: lTypeDevice
                text: qsTr("Последовательный порт:")
            }
            ComboBox {
                id: portList
                width: parent.width
                model: ListModel {
                    id: modelPortList
                }
            }
            Label {
                id: baudLabel
                text: qsTr("Скорость обмена данными")
            }
            ComboBox {
                id: baudRateList
                width: parent.width
                model: ListModel {
                    id: modelBaudrateList
                }
            }
            Row{
                ButtonRound {
                    id: buttonClose
                    useIcon: true
                    iconCode: "\uf00d  "
                    textLine: 2
                    widthBody: 110
                    textIsCenter: true
                    name: qsTr("Закрыть")
                    onClicked: {
                        abortConnectButton()
                    }
                }
                ButtonRound {
                    id: buttonAccept
                    textLine: 2
                    widthBody: 125
                    useIcon: true
                    iconCode: "\uF1E6  "
                    name: qsTr("Подключить")
                    onClicked: {
                        acceptConnectReady(portList.currentText, baudRateList.currentText)
                    }
                }
            }
        }
    }
}
