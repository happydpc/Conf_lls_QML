import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Dialogs 1.2

Rectangle {
    color: "#e7e9eb"

    //    width: 1000
    //    height: 600

    anchors.fill: parent

    function setNoActive() {
        devPropertyLlsTMK24.isEnabled = false
    }
    function setDevProperty(listProperty) {
        typeDeviceText.text = listProperty[0]
        snText.text = listProperty[1]
        netIdText.text = listProperty[2]
        versionFirmwareText.text = listProperty[4]
    }

    function setUpdateCurrentValues(data) {
        devPropertyLlsTMK24.isEnabled = true
        var values = viewController.getCurrentDevOtherData()
        if(values.length >0) {
            levelValue.text = values[0]
            levelProgress.value = values[1]
            cntValue.text = values[2]
            freqValue.text = values[3]
            tempValue.text = values[4]
        }
        //-- chart
        var list = viewController.getCurrentDevChart()
        series1.clear();
        graph.graphLength = list.length
        graph.graphAmplitudeMax = 0
        for(var i=0; i<list.length; i++) {
            if(graph.graphAmplitudeMax < parseInt(list[i])) {
                graph.graphAmplitudeMax = parseInt(list[i]);
            }
        }
        for(i=0; i<list.length; i++) {
            series1.append(i, parseInt(list[i]));
        }
    }
    Rectangle {
        id: devPropertyLlsTMK24
        property bool isEnabled: false
        anchors.fill: parent
        enabled: devPropertyLlsTMK24.isEnabled
        color: "#e7e9eb"

        TabBar {
            id: propertiesTabBar
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.top: row5.bottom
            anchors.right: tabBar.left
            anchors.left: parent.left
            anchors.topMargin: 20
            currentIndex: propertiesView.currentIndex

            TabButton {
                id: calibrationTab
                text: qsTr("Калибровка MinMax")
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
            TabButton {
                id: tempCompensationTab
                text: qsTr("Температурная \nкомпенсация")
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
        }

        Rectangle {
            anchors.top: propertiesTabBar.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.topMargin: 0
            SwipeView {
                id: propertiesView
                anchors.fill: parent
                currentIndex: propertiesTabBar.currentIndex

                // 1- calibration
                Item {
                    id: calibrationItem
                    Column {
                        spacing: 10
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent

                        Label {
                            text: qsTr("Задание границ измерения:")
                        }
                        Button {
                            id: buttonEmpty
                            text: "Пустой"
                            onClicked: {
                                dialogLevelSetEmpty.open()
                            }
                        }
                        Button {
                            id: buttonFull
                            text: "Полный"
                        }
                        Button {
                            id: buttonEdit
                            text: "Редактировать"
                        }
                        Label {
                            text: "Тип жидкости"
                        }
                        ComboBox {
                            id: typeFuel
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
                // 2- filtration
                Item {
                    id: filtrationItem
                    Column {
                        spacing: 10
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent

                        Label {
                            text: "Тип фильтрации:"
                        }
                        ComboBox {
                            id: typeFiltration
                            model: ListModel {
                                ListElement {
                                    text: "Выключена"
                                }
                                ListElement {
                                    text: "Усреднение"
                                }
                                ListElement {
                                    text: "Медиана"
                                }
                                ListElement {
                                    text: "Адаптивный"
                                }
                            }
                        }
                        Label {
                            text: "Время усреднения (0-21), с:"
                        }
                        SpinBox {
                            id: filterVvarageValueSec
                        }
                        Label {
                            text: "Длина медианы (0-7):"
                        }
                        SpinBox {
                            //                        id: filterVvarageValueSec
                        }
                        Label {
                            text: "Ковариация шума процесса (Q):"
                        }
                        SpinBox {
                            //                        id: filterVvarageValueSec
                        }
                        Label {
                            text: "Ковариация шума измерения (R):"
                        }
                        SpinBox {
                            //                        id: filterVvarageValueSec
                        }
                    }
                }
                // 3- temperature
                Item {
                    id: tempCompensationItem
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
                            model: ListModel {
                                ListElement {
                                    text: "Выключен"
                                }
                                ListElement {
                                    text: "АИ-95"
                                }
                                ListElement {
                                    text: "АИ-92"
                                }
                                ListElement {
                                    text: "АИ-80 (лето)"
                                }
                                ListElement {
                                    text: "АИ-80 (зима)"
                                }
                                ListElement {
                                    text: "ДТ (лето)"
                                }
                                ListElement {
                                    text: "ДТ (зима)"
                                }
                                ListElement {
                                    text: "Пользовательский"
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
                // base parameters
                Item {
                    id: basePropertiesItem
                    Column {
                        spacing: 10
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent
                        Button {
                            text: "Сменить сетевой адрес"
                            id: changeIdAddr
                        }
                        Label {
                            text: "Самостоятельная выдача данных:"
                        }
                        ComboBox {
                            id: typeIndependentOutMessage
                            model: ListModel {
                                ListElement {
                                    text: "Выключена"
                                }
                                ListElement {
                                    text: "Бинарная"
                                }
                                ListElement {
                                    text: "Символьная"
                                }
                            }
                        }
                        Label {
                            text: "Период выдачи данных (0-255), с:"
                        }
                        SpinBox {
                        }
                        Label {
                            text: "Мин. значение уровня (0-1023):"
                        }
                        SpinBox {
                        }
                        Label {
                            text: "Макс.значение уровня (0-4095):"
                        }
                        SpinBox {
                        }
                        Label {
                            text: "Параметр в выходном сообщении датчика:"
                        }
                        ComboBox {
                            id: typeOutMessage
                            width: 250
                            model: ListModel {
                                ListElement {
                                    text: "Относительный уровень"
                                }
                                ListElement {
                                    text: "Объем (по таблице таррировки)"
                                }
                            }
                        }
                        Label {
                            text: "Тип интерполяции:"
                        }
                        ComboBox {
                            id: typeInterpolation
                            model: ListModel {
                                ListElement {
                                    text: "Линейная"
                                }
                                ListElement {
                                    text: "Квадратичная"
                                }
                                ListElement {
                                    text: "Сплайновая"
                                }
                            }
                        }
                    }
                }
            }
        }


        TabBar {
            id: tabBar
            width: 300
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

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

                Rectangle {
                    id: currnetDataRect
                    width: tabBar.width
                    height: tabBar.height - currentData.height
                    color: "#ffffff"
                    anchors.topMargin: currentData.height
                    anchors.top: parent.top
                    anchors.left: parent.left
                    clip: true

                    Column {
                        id: column
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        spacing: 10

                        Label {
                            id: levelValue
                            text: qsTr("Level/value:")
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }

                        ProgressBar {
                            id: levelProgress
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            to: 100
                            value: 30

                            contentItem: Item {
                                implicitWidth: levelProgress.width
                                implicitHeight: 4

                                Rectangle {
                                    id: bar
                                    width: levelProgress.visualPosition * levelProgress.width
                                    height: levelProgress.height
                                    radius: 5
                                    color: "#416FE1"
                                }
                            }
                        }

                        Label {
                            id: label
                            text: qsTr("CNT:")
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                        }

                        TextField {
                            id: cntValue
                            height: 30
                            text: qsTr("0")
                            readOnly: true
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }

                        Label {
                            id: label1
                            text: qsTr("Temperature:")
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }

                        TextField {
                            id: tempValue
                            height: 30
                            text: qsTr("0")
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }

                        Label {
                            id: label2
                            text: qsTr("Frequency:")
                        }

                        TextField {
                            id: freqValue
                            height: 30
                            text: qsTr("0")
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }

                        ChartView {
                            id: graph
                            height: parent.height - 300
                            width: parent.width + 100
                            anchors.left: parent.left
                            anchors.leftMargin: -20
                            anchors.right: parent.right
                            anchors.rightMargin: -20
                            theme: ChartView.ChartThemeLight
                            title: "Value/Level"
                            antialiasing: true
                            visible: devPropertyLlsTMK24.isEnabled
                            property int graphLength: 1
                            property int graphAmplitudeMax: 1
                            ValueAxis {
                                id: axisX
                                min: 0
                                max: graph.graphLength
                                tickCount: 5
                            }
                            ValueAxis {
                                id: axisY
                                min: 0
                                max: graph.graphAmplitudeMax
                                tickCount: 5
                            }
                            LineSeries {
                                id: series1
                                axisX: axisX
                                axisY: axisY
                            }
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

        Row {
            id: row2
            height: 25
            spacing: 5
            clip: true
            anchors.right: tabBar.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            Row {
                id: row1
                clip: true
                anchors.right: row.left
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                width: row2.width / 2
                height: parent.height
                Label {
                    id: lSn
                    text: qsTr("Зав/ном:")
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                }

                TextField {
                    id: snText
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: lSn.right
                    anchors.leftMargin: 10
                    height: parent.height
                    readOnly: true
                }
            }

            Row {
                id: row
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                width: row2.width / 2
                height: parent.height
                Label {
                    id: lTypeDevice
                    text: qsTr("Тип датчика")
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }

                TextField {
                    id: typeDeviceText
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: lTypeDevice.right
                    anchors.leftMargin: 10
                    font.underline: false
                    readOnly: true
                    height: parent.height
                }
            }
        }

        Row {
            id: row5
            height: 25
            spacing: 5
            clip: true
            anchors.right: tabBar.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: row2.bottom
            anchors.topMargin: 10
            z: 2

            Row {
                id: row4
                height: parent.height
                clip: true
                anchors.right: row.left
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                width: row2.width / 2

                Label {
                    id: lNetId
                    text: qsTr("Сетевой адрес:")
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                }

                TextField {
                    id: netIdText
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: lNetId.right
                    anchors.leftMargin: 10
                    height: parent.height
                    readOnly: true
                }
            }

            Row {
                id: row6
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                width: row2.width / 2
                height: parent.height
                Label {
                    id: lversionFirmwareText
                    text: qsTr("Версия ПО")
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }

                TextField {
                    id: versionFirmwareText
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: lversionFirmwareText.right
                    anchors.leftMargin: 10
                    font.underline: false
                    height: parent.height
                    readOnly: true
                }
            }
        }
    }
    BusyIndicator {
        id: busyIndicator
        visible: devPropertyLlsTMK24.isEnabled ? false : true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Dialog {
        id: dialogLevelSetEmpty
        visible: false
        title: "Смена уровня Min-Max"
        standardButtons: StandardButton.Close | StandardButton.Apply
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Присвоить уровень \"Минимум\""
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            viewController.setCurrentDevLevelAsEmpty()
            close()
        }
    }
    Dialog {
        id: dialogLevelSetFull
        visible: false
        title: "Смена уровня Min-Max"
        standardButtons: StandardButton.Close | StandardButton.Apply
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Присвоить уровень \"Максимум\""
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            viewController.setCurrentDevLevelAsFull()
            close()
        }
    }
}
