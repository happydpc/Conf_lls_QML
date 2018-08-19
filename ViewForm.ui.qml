import QtQuick 2.4
import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import Qt.labs.calendar 1.0

Item {
    width: 1100
    height: 800
    property alias timeBar: timeBar
    Rectangle {
        id: view
        color: "#ffffff"
        anchors.fill: parent

        Rectangle {
            id: rectangle
            height: 60
            color: "#0029bb"
            radius: 15
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            Label {
                id: timeBar
                color: "#ffffff"
                text: qsTr("Label")
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            ToolButton {
                id: toolButton
                x: -452
                width: 50
                height: 60
                text: qsTr(": : :")
                flat: false
                highlighted: false
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
        }

        Rectangle {
            id: rectangle1
            color: "#ffffff"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: rectangle.bottom
            anchors.topMargin: 0

            Row {
                id: row55
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                layoutDirection: Qt.LeftToRight
                spacing: 15

                Rectangle {
                    id: rectangle3
                    width: parent.width / 2
                    height: parent.height
                    color: "#ecf1fc"
                    radius: 0

                    Flickable {
                        id: containerUsers
                        boundsBehavior: Flickable.DragAndOvershootBounds
                        flickableDirection: Flickable.VerticalFlick
                        contentHeight: 128
                        contentWidth: parent.width
                        anchors.fill: parent

                        Rectangle {
                            height: 3
                            color: "#0714ea"
                            radius: 0
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.right: parent.right
                            Label {
                                height: 128
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                color: "#000000"
                                text: "Иванов Vs Петров"
                                anchors.topMargin: -70
                                anchors.fill: parent
                                lineHeight: 0.9
                                renderType: Text.NativeRendering
                                font.pointSize: 26
                            }
                        }
                        Rectangle {
                            height: 3
                            color: "#0714ea"
                            radius: 0
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: -100
                            anchors.right: parent.right
                            Label {
                                height: 128
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                color: "#000000"
                                text: "Иванов Vs Петров"
                                anchors.topMargin: -70
                                anchors.fill: parent
                                lineHeight: 0.9
                                renderType: Text.NativeRendering
                                font.pointSize: 26
                            }
                        }
                    }
                }

                Rectangle {
                    id: rectangle2
                    width: parent.width / 2 - 15
                    height: parent.height
                    color: "#fdeded"
                }
            }
        }
    }
}
