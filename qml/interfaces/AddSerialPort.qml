import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "qrc:/qml/miscElems"

Popup {
    id: popup
    width: 450
    height: 270
    x: width
    y: height
    modal: true

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
        width: 400
        height: 200
        GroupBox {
            id: groupBoxSerialPort
            x: 9
            y: 8
            width: 382
            height: 171
            title: qsTr("Последовательный порт:")

            Row {
                id: row_1
                x: -12
                y: -171
                height: 46
                anchors.top: parent.top
                anchors.topMargin: 6
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 10

                ComboBox {
                    id: portList
                    editable: true
                    model: ListModel {
                        id: modelPortList
                    }
                }

                ButtonRound {
                    id: buttonAccept
                    x: 250
                    y: 0
                    textLine: 2
                    widthBody: 100
                    name: qsTr("Подкл.")
                    onClicked: {
                        acceptConnectReady(portList.currentText, baudRateList.currentText)
                    }
                }

                ButtonRound {
                    id: buttonUpdate
                    x: 145
                    y: 0
                    textLine: 2
                    enabled: false
                    name: qsTr("Обновить")
                }
            }

            Row {
                id: row_2
                x: -12
                y: -115
                height: 43
                ComboBox {
                    id: baudRateList
                    editable: true
                    model: ListModel {
                        id: modelBaudrateList
                    }
                }
                Label {
                    id: baudLabel
                    text: qsTr("Скорость обмена данными")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: baudRateList.right
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }
            }
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 1
                color: "#e0e5ef"
                samples: 10
                radius: 20
            }
        }

        ButtonRound {
            id: buttonClose
            x: 8
            y: 193
            textLine: 2
            widthBody: 140
            textIsCenter: true
            name: qsTr("Закрыть")
            onClicked: {
                console.log("button Close clicked")
                abortConnectButton()
            }
        }
    }
}
