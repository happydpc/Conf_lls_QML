import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Dialog {
    visible: false
    property string messageTitle: ""
    property string messageText: ""
    title: messageTitle
    standardButtons: StandardButton.Close | StandardButton.Apply
    function setData(textTitle, textMessage) {
        messageTitle = textTitle
        messageText = textMessage
    }
    Rectangle {
        color: "transparent"
        implicitWidth: 500
        implicitHeight: 300
        Text {
            text: messageText
            color: "black"
            anchors.centerIn: parent
        }
    }
    onOpened:  {
        timerUntili.start()
    }

    Timer {
        id: timerUntili
        interval: 3000
        running: false
        repeat: false
        onTriggered: {
            messageShow.close()
        }
    }
}
