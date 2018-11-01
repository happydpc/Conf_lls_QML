import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Rectangle {
    property string typeLogo: ""

    Component.onCompleted: {
        typeLogo = viewController.getTypeLogo()
    }

    color: "#ffffff"
    Image {
        source: typeLogo === "progress" ? ("qrc:/logo/images/logo/logo_progress.png") : (typeLogo === "gs" ? "qrc:/logo/images/logo/logo_gls.png" : "")
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 150
        anchors.bottomMargin: 150
        anchors.rightMargin: 200
        anchors.leftMargin: 200
    }

}
