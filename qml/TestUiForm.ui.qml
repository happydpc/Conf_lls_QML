import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Popup {
    id: addDeviceTarirDialog
    modal: true
    width: 500
    height: 300

    //    y: width / 2
    //    x: height / 2
    Rectangle {
        id: rectangle
        anchors.fill: parent

        ListView {
            id: tarDevListView
            anchors.bottom: rectangle.bottom
            anchors.top: rectangle.top
            anchors.left: rectangle.left
            anchors.right: rectangle.right
            ScrollBar.vertical: ScrollBar {
                width: 20
            }
            delegate: Item {
                id: tarDevListViewDelegate
                height: 30
                width: parent.width

                Rectangle {
                    width: parent.width
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    height: parent.height
                    color: "transparent"
                    TextField {
                        id: deviceTypeName
                        height: 20
                        text: model.deviceTypeName
                        font.bold: false
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        readOnly: true
                        background: "#ded3d3"
                    }
                    TextField {
                        id: deviceId
                        height: 20
                        text: model.deviceId
                        font.bold: false
                        anchors.top: deviceTypeName.bottom
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        readOnly: true
                        background: "#c4e7c3"
                    }
                    TextField {
                        id: deviceSerialNumber
                        height: 20
                        text: model.deviceSerialNumber
                        font.bold: false
                        anchors.top: deviceId.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        readOnly: true
                        background: "#e7e1c0"
                    }
                }
            }
            model: ListModel {
                id: tarDevListModel
            }
        }
    }
}
