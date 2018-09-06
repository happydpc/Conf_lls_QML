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

        SwipeView {
            id: propertiesView
            x: 0
            anchors.top: tabBar2.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.topMargin: 0

            currentIndex: 0

            Item {
                id: basePropertiesItem
                anchors.fill: parent
                Column {
                    spacing: 10
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.fill: parent
                    Label {
                        text: "11111"
                    }
                }
            }
            Item {
                id: basePropertiesItem2
                anchors.fill: parent
                Column {
                    spacing: 10
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.fill: parent
                    Label {
                        text: "2222"
                    }
                }
            }
        }
    }
}

            //        TabBar {
            //            id: propertiesTab
            //            width: 50
            //            anchors.top: parent.top
            //            anchors.topMargin: 0
            //            anchors.left: parent.left
            //            anchors.right: parent.right
            //            TabButton {
            //                id: basePropertiesTab
            //                text: qsTr("Общие параметры")
            //                focusPolicy: Qt.TabFocus
            //                background: Rectangle {
            //                    gradient: Gradient {
            //                        GradientStop {
            //                            position: 1
            //                            color: "#4D75E0"
            //                        }
            //                        GradientStop {
            //                            position: 0
            //                            color: "#EEF0F6"
            //                        }
            //                    }
            //                }
            //            }

            //            TabButton {
            //                id: tempCompensationTab
            //                text: qsTr("Температурная компенсация")
            //                background: Rectangle {
            //                    gradient: Gradient {
            //                        GradientStop {
            //                            position: 1
            //                            color: "#4D75E0"
            //                        }
            //                        GradientStop {
            //                            position: 0
            //                            color: "#EEF0F6"
            //                        }
            //                    }
            //                }
            //            }

            //            TabButton {
            //                id: filtrationTab
            //                text: qsTr("Фильтрация")
            //                background: Rectangle {
            //                    gradient: Gradient {
            //                        GradientStop {
            //                            position: 1
            //                            color: "#4D75E0"
            //                        }
            //                        GradientStop {
            //                            position: 0
            //                            color: "#EEF0F6"
            //                        }
            //                    }
            //                }
            //            }
            //        }

            //        Item {
            //            id: filtration
            //        }

            //        SwipeView {
            //            id: propertiesView
            //            x: 0
            //            y: 50
            //            anchors.top: propertiesTab.bottom
            //            anchors.right: parent.right
            //            anchors.bottom: parent.bottom
            //            anchors.left: parent.left
            //            anchors.topMargin: 0

            //            currentIndex: 0

            //            Item {
            //                id: basePropertiesItem
            //                anchors.fill: parent
            //                Column {
            //                    spacing: 10
            //                    anchors.topMargin: 20
            //                    anchors.bottomMargin: 20
            //                    anchors.rightMargin: 20
            //                    anchors.leftMargin: 20
            //                    anchors.fill: parent
            //                    Label {
            //                        text: "Сетевой адрес (1-254)"
            //                    }
            //                    Button {
            //                        id: changeIdAddr
            //                    }
            //                    Label {
            //                        text: "Самостоятельная выдача данных:"
            //                    }
            //                    ComboBox {
            //                        id: typeIndependentOutMessage
            //                        model: ListModel {
            //                            ListElement {
            //                                text: "Выключена"
            //                            }
            //                            ListElement {
            //                                text: "Бинарная"
            //                            }
            //                            ListElement {
            //                                text: "Символьная"
            //                            }
            //                        }
            //                    }
            //                    Label {
            //                        text: "Период выдачи данных (0-255), с:"
            //                    }
            //                    SpinBox {
            //                    }
            //                    Label {
            //                        text: "Мин. значение уровня (0-1023):"
            //                    }
            //                    SpinBox {
            //                    }
            //                    Label {
            //                        text: "Макс.значение уровня (0-4095):"
            //                    }
            //                    SpinBox {
            //                    }
            //                    Label {
            //                        text: "Параметр в выходном сообщении датчика:"
            //                    }
            //                    ComboBox {
            //                        id: typeOutMessage
            //                        model: ListModel {
            //                            ListElement {
            //                                text: "Относительный уровень"
            //                            }
            //                            ListElement {
            //                                text: "Объем (по таблице таррировки)"
            //                            }
            //                        }
            //                    }
            //                }
            //            }

            //            Item {
            //                id: tempCompensationItem
            //                anchors.fill: parent
            //                Column {
            //                    spacing: 10
            //                    anchors.topMargin: 20
            //                    anchors.bottomMargin: 20
            //                    anchors.rightMargin: 20
            //                    anchors.leftMargin: 20
            //                    anchors.fill: parent

            //                    Label {
            //                        text: qsTr("Температурная компенсация линейного расширения топлива")
            //                        anchors.left: parent.left
            //                        anchors.leftMargin: 0
            //                        anchors.right: parent.right
            //                        anchors.rightMargin: 0
            //                    }
            //                    Label {
            //                        text: qsTr("Режим:")
            //                        anchors.left: parent.left
            //                        anchors.leftMargin: 0
            //                        anchors.right: parent.right
            //                        anchors.rightMargin: 0
            //                    }
            //                    ComboBox {
            //                        id: typeTempCompensation
            //                        model: ListModel {
            //                            ListElement {
            //                                text: "Выключен"
            //                            }
            //                            ListElement {
            //                                text: "АИ-95"
            //                            }
            //                        }
            //                    }
            //                    Label {
            //                        text: qsTr("K1:")
            //                        anchors.left: parent.left
            //                        anchors.leftMargin: 0
            //                        anchors.right: parent.right
            //                        anchors.rightMargin: 0
            //                    }
            //                    TextField {
            //                        id: k1
            //                        text: "0.0"
            //                    }
            //                    Label {
            //                        text: qsTr("K2:")
            //                        anchors.left: parent.left
            //                        anchors.leftMargin: 0
            //                        anchors.right: parent.right
            //                        anchors.rightMargin: 0
            //                    }
            //                    TextField {
            //                        id: k2
            //                        text: "0.0"
            //                    }
            //                }
            //            }
            //            Item {
            //                id: calibrationItem
            //                anchors.fill: parent
            //                Column {
            //                    spacing: 10
            //                    anchors.topMargin: 20
            //                    anchors.bottomMargin: 20
            //                    anchors.rightMargin: 20
            //                    anchors.leftMargin: 20
            //                    anchors.fill: parent

            //                    Label {
            //                        text: qsTr("Задание границ измерения:")
            //                    }
            //                    Button {
            //                        id: buttonEmpty
            //                        text: "Пустой"
            //                    }
            //                    Button {
            //                        id: buttonFull
            //                        text: "Полный"
            //                    }
            //                    Button {
            //                        id: buttonEdit
            //                        text: "Редактировать"
            //                    }
            //                    Label {
            //                        text: "Тип жидкости"
            //                    }
            //                    ComboBox {
            //                        id: typeFuel
            //                        model: ListModel {
            //                            ListElement {
            //                                text: "Топливо"
            //                            }
            //                            ListElement {
            //                                text: "Вода"
            //                            }
            //                        }
            //                    }
            //                }
            //            }
            //            Item {
            //                id: filtrationItem
            //                anchors.fill: parent
            //                Column {
            //                    spacing: 10
            //                    anchors.topMargin: 20
            //                    anchors.bottomMargin: 20
            //                    anchors.rightMargin: 20
            //                    anchors.leftMargin: 20
            //                    anchors.fill: parent

            //                    Label {
            //                        text: qsTr("Фильтрация:")
            //                        anchors.left: parent.left
            //                        anchors.leftMargin: 0
            //                        anchors.right: parent.right
            //                        anchors.rightMargin: 0
            //                    }
            //                    Label {
            //                        text: "Тип фильтрации:"
            //                    }
            //                    ComboBox {
            //                        id: typeFiltration
            //                        model: ListModel {
            //                            ListElement {
            //                                text: "Выключена"
            //                            }
            //                        }
            //                    }
            //                    Label {
            //                        text: "Время усреднения (0-21), с:"
            //                    }
            //                    SpinBox {
            //                        id: filterVvarageValueSec
            //                    }
            //                    Label {
            //                        text: "Длина медианы (0-7):"
            //                    }
            //                    SpinBox {
            //                        //                        id: filterVvarageValueSec
            //                    }
            //                    Label {
            //                        text: "Ковариация шума процесса (Q):"
            //                    }
            //                    SpinBox {
            //                        //                        id: filterVvarageValueSec
            //                    }
            //                    Label {
            //                        text: "Ковариация шума измерения (R):"
            //                    }
            //                    SpinBox {
            //                        //                        id: filterVvarageValueSec
            //                    }
            //                }
            //            }
            //        }
            //    }

            //    PageIndicator {
            //        id: propertiesIndicator
            //        x: 476
            //        y: 580

            //        count: propertiesView.count
            //        currentIndex: propertiesView.currentIndex

            //        anchors.bottom: propertiesView.bottom
            //        anchors.horizontalCenter: parent.horizontalCenter
            //    }

