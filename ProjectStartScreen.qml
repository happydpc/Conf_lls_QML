import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    id:projectStartScreen
    Rectangle {
        color: "#ffffff"
        anchors.fill: parent

        Image {
            id: logo
            source: "/images/logo/logo_progress.png"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 100
            anchors.bottomMargin: 100
            anchors.rightMargin: 200
            anchors.leftMargin: 200
        }
    }
}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
