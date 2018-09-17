import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Popup {
    id: popup
    width: 450
    height: 270
    property alias buttonUpdate: buttonUpdate
    property alias buttonAccept: buttonAccept
    property alias buttonClose: buttonClose
    property alias portList: portList
    property alias baudRateList: baudRateList
    dim: false
    clip: false

    modal: true

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
                }

                ButtonRound {
                    id: buttonUpdate
                    x: 8
                    y: 193
                    textLine: 2
                    widthBody: 100
                    enabled: false
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: portList.left
                    anchors.leftMargin: 150
                    name: qsTr("Обновить")
                }
                //                Button {
                //                    id: buttonAccept
                //                    width: 110
                //                    height: 40
                //                    text: qsTr("Подсоединить")
                //                    anchors.right: parent.right
                //                    anchors.rightMargin: 0
                //                }
                //                Button {
                //                    id: buttonUpdate
                //                    width: 80
                //                    height: 40
                //                    text: qsTr("Обновить")
                //                    enabled: false
                //                    anchors.top: parent.top
                //                    anchors.topMargin: 0
                //                    anchors.left: portList.left
                //                    anchors.leftMargin: 150
                //                }
            }

            Row {
                id: row_2
                x: -12
                y: -115
                height: 43
                anchors.top: row_1.bottom
                anchors.topMargin: 6
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10

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

            name: qsTr("Закрыть")
        }
    }
}
