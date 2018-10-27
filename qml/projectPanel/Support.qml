import QtQuick 2.9
import QtQuick.Dialogs 1.2

Dialog {
    visible: false
    title: "Поддержка"
    standardButtons: StandardButton.Close
    Rectangle {
        color: "transparent"
        implicitWidth: 500
        implicitHeight: 80
        Text {
            anchors.centerIn: parent
            text: "<a href='https://progress-system.com'>progress-system.com</a>"
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}
