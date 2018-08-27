import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Rectangle {
    id: devPropertyLlsTMK24
    color: "#e7e9eb"

    //    width: 800
    //    height: 500

    anchors.fill: parent
    TabBar {
        id: tabBar
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: deviceProperties.width / 3
        TabButton {
            id: currentData
            text: qsTr("Текущие данные")
            focusPolicy: Qt.TabFocus
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }

        TabButton {
            id: slaves
            text: qsTr("Ведомые")
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }

        TabButton {
            id: log
            text: qsTr("Журнал")
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }
    }

    GridLayout {
        id: gridLayout
        columnSpacing: 5
        anchors.right: tabBar.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 1.5
        anchors.top: parent.top
        anchors.topMargin: 10
        rowSpacing: 5
        rows: 3
        columns: 2

        Label {
            id: lTypeDevice
            height: typeDeviceText.height
            text: qsTr("Тип датчика")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: typeDeviceText
            text: qsTr("")
            font.underline: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: lTypeDevice.left
            anchors.leftMargin: 150
            readOnly: true
        }

        Label {
            id: lSn
            height: typeDeviceText.height
            text: qsTr("Заводской номер")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: snText
            text: qsTr("")
            anchors.left: lSn.left
            anchors.leftMargin: 150
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Label {
            id: lVersionFirmware
            height: typeDeviceText.height
            text: qsTr("Версия ПО")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: versionFirmwareText
            text: qsTr("")
            anchors.left: lVersionFirmware.left
            anchors.leftMargin: 150
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Label {
            id: lNetId
            height: typeDeviceText.height
            text: qsTr("Сетевой адрес")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: netIdText
            text: qsTr("")
            anchors.left: lVersionFirmware.left
            anchors.leftMargin: 150
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
    }

    TabBar {
        id: tabBar2
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: gridLayout.bottom
        anchors.right: tabBar.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 10

        TabButton {
            id: currentData2
            text: qsTr("Текущие данные")
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }

        TabButton {
            id: slaves2
            text: qsTr("Ведомые")
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }

        TabButton {
            id: log2
            text: qsTr("Журнал")
            background: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 1
                        color: "#4D75E0"
                    }
                    GradientStop {
                        position: 0
                        color: "#EEF0F6"
                    }
                }
            }
        }
    }
}

/*##^## Designer {
    D{i:27;anchors_height:241;anchors_width:515;anchors_x:32;anchors_y:70}
}
 ##^##*/
