import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3

Popup {
    width: 300
    height: 280

    x: parent.width / 2

    //        width: 500
    //        height: 280

    //        anchors.centerIn: 100//parent
    modal: true
    ////        verticalCenter: parent
    ////        horizontalCenter: parent

    ////        y: 200
    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        Column {
            id: column
            anchors.bottomMargin: 15
            anchors.fill: parent
        }

        ComboBox {
            id: comboBox
            x: 8
            y: 12
        }

        Label {
            id: label
            x: 164
            y: 83
            text: qsTr("Скорость")
        }

        Button {
            id: refreshPort
            x: 164
            y: 12
            width: 128
            height: 40
            text: qsTr("Обновить")
        }

        ComboBox {
            id: comboBox1
            x: 8
            y: 69
        }

        SpinBox {
            id: spinBox
            x: 8
            y: 140
        }

        Button {
            id: button
            x: 164
            y: 140
            width: 128
            height: 40
            text: qsTr("Найти")
        }

        Button {
            id: button1
            x: 164
            y: 206
            width: 128
            height: 66
            text: qsTr("Принять")
        }

        Button {
            id: button2
            x: 8
            y: 206
            width: 140
            height: 66
            text: qsTr("Закрыть")
        }
    }

    Label {
        id: label1
        x: 38
        y: 120
        text: qsTr("Адрес датчика")
    }
}
