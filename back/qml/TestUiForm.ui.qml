import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Popup {
    id: addDeviceTarirDialog
    modal: true
    width: 450
    height: 275

    //    y: width / 2
    //    x: height / 2
    Rectangle {
        id: rectangle
        anchors.fill: parent

        Button {
            id: acceptButton
            x: 235
            y: 220
            width: 172
            height: 40
            text: qsTr("Сменить")
        }

        Button {
            id: exitButton
            x: 45
            y: 220
            width: 184
            height: 40
            text: qsTr("Закрыть")
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
}
