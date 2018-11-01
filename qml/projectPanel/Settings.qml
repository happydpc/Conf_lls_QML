import QtQuick 2.9
import QtQuick.Dialogs 1.2

Dialog {
    visible: false
    title: "Проверка обновлений"
    standardButtons: StandardButton.Close | StandardButton.Ok
    Rectangle {
        color: "transparent"
        implicitWidth: 400
        implicitHeight: 100
        Text {
            anchors.centerIn: parent
            text: qsTr("Проверить обновления?")
        }
    }
    onAccepted: {
        viewController.checkUpdateVersionSoftware()
        close()
    }
}
