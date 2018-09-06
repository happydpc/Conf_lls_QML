import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0

import QtGraphicalEffects 1.0

Rectangle {
    color: "#e7e9eb"
    width: 1000
    height: 600

    Rectangle {
        id: devPropertyLlsTMK24
        property bool isEnabled: false
        color: "#e7e9eb"
        anchors.fill: parent
        enabled: devPropertyLlsTMK24.isEnabled

        TabBar {
            id: propertiesTab
            width: 50
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            TabButton {
                id: basePropertiesTab
                text: qsTr("Общие параметры")
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
                id: tempCompensationTab
                text: qsTr("Температурная компенсация")
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
                id: filtrationTab
                text: qsTr("Фильтрация")
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

        Item {
            id: filtration
        }

        SwipeView {
            id: propertiesView
            x: 0
            y: 50
            anchors.top: propertiesTab.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 0

            currentIndex: 3

            Item {
                id: baseProperties
            }

            Item {
                id: tempCompensation
                anchors.fill: parent
                Column {
                    spacing: 10
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.fill: parent

                    Label {
                        text: qsTr("Температурная компенсация линейного расширения топлива")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Label {
                        text: qsTr("Режим:")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    ComboBox {
                        id: typeTempCompensation
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        model: ListModel {
                            ListElement {
                                text: "Выключен"
                            }
                            ListElement {
                                text: "АИ-95"
                            }
                        }
                    }
                    Label {
                        text: qsTr("K1:")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    TextField {
                        id: k1
                        text: "0.0"
                    }
                    Label {
                        text: qsTr("K2:")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    TextField {
                        id: k2
                        text: "0.0"
                    }
                }
            }
            Item {
                id: calibration
                anchors.fill: parent
                Column {
                    spacing: 10
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.fill: parent

                    Label {
                        text: qsTr("Задание границ измерения:")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonEmpty
                        text: "Пустой"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonFull
                        text: "Полный"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonEdit
                        text: "Редактировать"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Label {
                        text: "Тип жидкости"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    ComboBox {
                        id: typeFuel
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        model: ListModel {
                            ListElement {
                                text: "Топливо"
                            }
                            ListElement {
                                text: "Вода"
                            }
                        }
                    }
                }
            }
            Item {
                anchors.fill: parent
                Column {
                    spacing: 10
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.fill: parent

                    Label {
                        text: qsTr("Фильтрация:")
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonEmpty
                        text: "Пустой"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonFull
                        text: "Полный"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Button {
                        id: buttonEdit
                        text: "Редактировать"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    Label {
                        text: "Тип жидкости"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                    ComboBox {
                        id: typeFuel
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        model: ListModel {
                            ListElement {
                                text: "Топливо"
                            }
                            ListElement {
                                text: "Вода"
                            }
                        }
                    }
                }
            }
        }
    }

    PageIndicator {
        id: propertiesIndicator
        x: 476
        y: 580

        count: propertiesView.count
        currentIndex: propertiesView.currentIndex

        anchors.bottom: propertiesView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
} //    SwipeView {//        id: currnetDataRect//        x: 0//        y: 28//        width: tabBar.width//        height: tabBar.height - currentData.height//        currentIndex: 0//        anchors.topMargin: currentData.height
//        anchors.top: parent.top
//        anchors.left: parent.left

//        Rectangle {
//            id: rectangle
//            x: 0
//            y: 0
//            width: 707
//            height: 453
//            color: "#ffffff"

//            Column {
//                id: column
//                x: 0
//                y: 0
//                width: 847
//                height: 406
//                spacing: 10

//                Label {
//                    id: levelValue
//                    text: qsTr("Level/value:")
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                }

//                ProgressBar {
//                    id: levelProgress
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                    to: 100
//                    value: 30

//                    contentItem: Item {
//                        implicitWidth: levelProgress.width
//                        implicitHeight: 4

//                        Rectangle {
//                            id: bar
//                            width: levelProgress.visualPosition * levelProgress.width
//                            height: levelProgress.height
//                            radius: 5
//                            color: "#416FE1"
//                        }
//                    }
//                }

//                Label {
//                    id: label
//                    text: qsTr("CNT:")
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                }

//                TextField {
//                    id: cntValue
//                    height: 30
//                    text: qsTr("0")
//                    readOnly: true
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                }

//                Label {
//                    id: label1
//                    text: qsTr("Temperature:")
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                }

//                TextField {
//                    id: tempValue
//                    height: 30
//                    text: qsTr("0")
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                }

//                Label {
//                    id: label2
//                    text: qsTr("Frequency:")
//                }

//                TextField {
//                    id: freqValue
//                    height: 30
//                    text: qsTr("0")
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                }
//            }
//        }

//        Button {
//            id: button
//            x: 0
//            y: 0
//            text: qsTr("Button")
//        }
//    }

