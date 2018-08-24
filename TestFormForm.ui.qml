import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0

Rectangle {
    id: deviceList
    border.color: "#A4A4A4"
    height: 500
    width: 200

    anchors.top: menuMain.bottom
    anchors.topMargin: 20
    anchors.bottom: parent.bottom
    Item {
        anchors.fill: parent
        ListView {
            id: listView
            maximumFlickVelocity: 100

            anchors.fill: parent
            spacing: 0
            delegate: Item {
                height: 50
                Button {
                    //                        Rectangle {
                    //                            anchors.fill: parent
                    //                            height: parent.height
                    //                            width: deviceList.width
                    //                            color: colorCode
                    //                            radius: 5
                    //                        }
                    text: name
                    font.bold: false
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            model: ListModel {
                ListElement {
                    name: "COM9"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#F2F2F2"
                }

                ListElement {
                    name: "ТМК3.24 (ID-2)"
                    colorCode: "#F2F2F2"
                }

                ListElement {
                    name: "COM21"
                    colorCode: "#81DAF5"
                }

                ListElement {
                    name: "ТМК3.24 (ID-1)"
                    colorCode: "#F2F2F2"
                }
            }

            Slider {
                id: slider
                x: 115
                y: 248
                orientation: Qt.Vertical
                value: 0.5
            }
        }
    }
}
