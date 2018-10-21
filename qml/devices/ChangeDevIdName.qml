import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import "qrc:/qml/miscElems"

Popup {
    modal: true
    width: 450
    height: 300
    y: width / 2
    x: height / 2

    Rectangle {
        id: rectangle
        anchors.fill: parent

        ButtonRound {
            id: acceptButton
            x: 235
            y: 220
            textLine:2
            textIsCenter: true
            widthBody: 175
            name: qsTr("Сменить")
            onClicked: {
                dialogChangeId.open()
                close()
            }
            Dialog {
                id: dialogChangeId
                visible: false
                title: "Смена ID адреса"
                standardButtons: StandardButton.Close | StandardButton.Apply
                Rectangle {
                    color: "transparent"
                    implicitWidth: 250
                    implicitHeight: 100
                    Text {
                        text: "Сменить адрес устройства?"
                        color: "black"
                        anchors.centerIn: parent
                    }
                }
                onApply: {
                    var tNewId = newIdAddress.value
                    var tPassword = ""
                    var tCurrentId = currentId.text
                    viewController.setCurrentDevChangeId(tPassword, tNewId, tCurrentId)
                    close()
                }
            }
        }

        ButtonRound {
            id: exitButton
            x: 45
            y: 220
            widthBody: 180
            textLine: 2
            name: qsTr("Закрыть")
            onClicked: {
                close()
            }
        }

        Label {
            id: label
            x: 45
            y: 23
            text: qsTr("Текущий адрес:")
        }

        TextField {
            id: currentId
            x: 207
            y: 16
            text: qsTr("0")
            readOnly: true
        }

        Label {
            id: label1
            x: 45
            y: 89
            text: qsTr("Новый адрес:")
        }

        TextField {
            id: password
            x: 45
            y: 135
            width: 362
            height: 40
            text: qsTr("")
            placeholderText: "Настроечный пароль"
        }

        SpinBox {
            id: newIdAddress
            x: 207
            y: 77
            width: 200
            height: 40
            to: 254
            from: 1
            value: 1
        }
    }

    onOpened: {
        var devProperty = viewController.getCurrentDevProperty()
        var devId = devProperty[6]
        currentId.text = devId
   }
}
