import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick 2.4
import QtQuick.Layouts 1.1

Popup {
    signal accept()
    signal exit()

    Column {
        id: column
        spacing: 10
        anchors.fill: parent
        Label {
            text: qsTr("ID текущий:")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: currentId
            text: "1"
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            readOnly: true
        }
        Label {
            text: qsTr("ID новый:")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        SpinBox {
            id: idNew
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            to: 254
            from: 1
            value: 1
        }
        Label {
            text: qsTr("Проверочный пароль:")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: passwordCheck
            text: ""
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            readOnly: true
            echoMode: TextInput.Password
        }
        Button {
            id: accept
            text: qsTr("Сменить")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
        Button {
            id: exit
            text: qsTr("Выйти")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }
}
