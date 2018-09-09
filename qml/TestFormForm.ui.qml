import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0

import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4

Rectangle {
    color: "#e7e9eb"
    width: 500
    height: 300

    Rectangle {
        id: rectangle
        clip: true
        anchors.fill: parent

        Column {
            spacing: 10
            anchors.fill: parent

            ScrollBar.vertical: ScrollBar {
                id: scrollDeviceList
                width: 20
            }

            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    font.pointSize: 8
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
            Row {
                width: 500
                height: 25
                spacing: 5
                clip: true
                TextField {
                    text: qsTr("")
                    height: parent.height
                    readOnly: true
                }
            }
        }

        SpinBox {
            id: spinBox
            x: 302
            y: 136
            from: 1
            value: 1
            to: 4095
        }
    }
}
