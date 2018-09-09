import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Dialogs 1.2

Rectangle {
    color: "#e7e9eb"
    anchors.fill: parent

    property alias messageMinMaxWriteOk: messageMinMaxWriteOk
    property alias messageReadSettingsOk: messageReadSettingsOk
    property alias messageWriteSettingsOk: messageWriteSettingsOk
    property alias messageReadErrorsOk: messageReadErrorsOk

    function setNoReady() {
        devPropertyProgressTmk24.isReady = false
    }
    function setDevProperty(listProperty) {
        typeDeviceText.text = listProperty[2]
        snText.text = listProperty[0]
        netIdText.text = listProperty[1]
        versionFirmwareText.text = listProperty[3]
        listProperty.splice(0, 6)
        readSettings("", listProperty)
    }

    function setUpdateCurrentValues(data) {
        devPropertyProgressTmk24.isReady = true
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
        logListView.positionViewAtEnd()
    }

    function addLogMessage(codeMessage, message) {
        logListModel.append({"message":message,"status":codeMessage})
    }

    function readSettings(devName, settings) {
        k1.text = settings[0]
        k2.text = settings[1]
        typeTempCompensation.currentIndex = settings[2] //        ret << QString::number(lls_data.settings.get.value.thermoCompensationType);
        periodicSendType.currentIndex = settings[3]     //        ret << QString::number(lls_data.settings.get.value.periodicSendType);
        periodicSendTime.value = settings[4]    //        ret << QString::number(lls_data.settings.get.value.periodicSendTime);
        typeOutMessage.currentIndex = settings[5]    //        ret << QString::number(lls_data.settings.get.value.outputValue);
        typeInterpolation.currentIndex = settings[6]    //        ret << QString::number(lls_data.settings.get.value.interpolationType);
        typeFiltration.currentIndex = settings[7]   //        ret << QString::number(lls_data.settings.get.value.filterType);
        filterLenghtMediana.value = settings[8] //        ret << QString::number(lls_data.settings.get.value.medianLength);
        filterAvarageValueSec.value = settings[9]   //        ret << QString::number(lls_data.settings.get.value.avarageLength);
        filterValueR.value= settings[10]   //        ret << QString::number(lls_data.settings.get.value.q, 'f');
        filterValueQ.value = settings[11]   //        ret << QString::number(lls_data.settings.get.value.r, 'f');
        minLevelValue.value = settings[12]  //      ret << QString::number(lls_data.settings.get.value.minLevel);
        maxLevelValue.value = settings[13]  //      ret << QString::number(lls_data.settings.get.value.maxLevel);
        //        ret << QString::number(lls_data.settings.get.value.rs232Speed);
        //        ret << QString::number(lls_data.settings.get.value.rs485Speed);
        //        ret << QString::number(lls_data.settings.get.value.slaveCount);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[0]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[1]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[2]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[3]);
    }
    function writeSettings() {
        var settings = [];
        settings.push(k1.text)
        settings.push(k2.text)
        settings.push(typeTempCompensation.currentIndex) //        ret << QString::number(lls_data.settings.get.value.thermoCompensationType);
        settings.push(periodicSendType.currentIndex)     //        ret << QString::number(lls_data.settings.get.value.periodicSendType);
        settings.push(periodicSendTime.value)    //        ret << QString::number(lls_data.settings.get.value.periodicSendTime);
        settings.push(typeOutMessage.currentIndex)    //        ret << QString::number(lls_data.settings.get.value.outputValue);
        settings.push(typeInterpolation.currentIndex)    //        ret << QString::number(lls_data.settings.get.value.interpolationType);
        settings.push(typeFiltration.currentIndex)   //        ret << QString::number(lls_data.settings.get.value.filterType);
        settings.push(filterLenghtMediana.value) //        ret << QString::number(lls_data.settings.get.value.medianLength);
        settings.push(filterAvarageValueSec.value)   //        ret << QString::number(lls_data.settings.get.value.avarageLength);
        settings.push(filterValueR.value)   //        ret << QString::number(lls_data.settings.get.value.q, 'f');
        settings.push(filterValueQ.value)   //        ret << QString::number(lls_data.settings.get.value.r, 'f');
        settings.push(minLevelValue.value)  //      ret << QString::number(lls_data.settings.get.value.minLevel);
        settings.push(maxLevelValue.value)  //      ret << QString::number(lls_data.settings.get.value.maxLevel);
        //        ret << QString::number(lls_data.settings.get.value.rs232Speed);
        //        ret << QString::number(lls_data.settings.get.value.rs485Speed);
        //        ret << QString::number(lls_data.settings.get.value.slaveCount);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[0]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[1]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[2]);
        //        ret << QString::number(lls_data.settings.get.value.slaveAddr[3]);
        viewController.setCurrentDevSettings(settings)
    }
    function readErrors(devName, errors) {
        error1Label.error1 = errors[0]
        error2Label.error2 = errors[1]
        error3Label.error3 = errors[2]
        error4Label.error4 = errors[3]
        error5Label.error5 = errors[4]
        error6Label.error6 = errors[5]
        error7Label.error7 = errors[6]
        error8Label.error8 = errors[7]
    }

    Rectangle {
        id: devPropertyProgressTmk24
        property bool isReady: false
        anchors.fill: parent
        enabled: devPropertyProgressTmk24.isReady
        color: "#e7e9eb"

        TabBar {
            id: propertiesTabBar
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.top: row7.bottom
            anchors.right: rightTabBarRect.left
            anchors.left: parent.left
            width: 1000
            currentIndex: propertiesView.currentIndex
            font.pointSize: 8

            TabButton {
                id: calibrationTab
                text: qsTr("Калибровка\nMinMax")
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
                text: qsTr("Тем-ная\nкомпенсация")
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
                text: qsTr("Общие\nпараметры")
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
                id: erorrsTab
                text: qsTr("Ошибки")
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
                id: masterSlaveTab
                text: qsTr("Ведущий/ведомый")
                enabled: false
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
                id: tarTab
                text: qsTr("Тарировка")
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
                            onClicked: {
                                dialogLevelSetFull.open()
                            }
                        }
                        Button {
                            id: buttonEdit
                            text: "Редактировать"
                            enabled: false
                        }
                        Label {
                            text: "Тип жидкости"
                        }
                        ComboBox {
                            id: typeFuel
                            height: 25
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
                            height: 25
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
                            id: filterAvarageValueSec
                            height: 25
                        }
                        Label {
                            text: "Длина медианы (0-7):"
                        }
                        SpinBox {
                            id: filterLenghtMediana
                            height: 25
                        }
                        Label {
                            text: "Ковариация шума процесса (Q):"
                        }
                        SpinBox {
                            id: filterValueQ
                            height: 25
                        }
                        Label {
                            text: "Ковариация шума измерения (R):"
                        }
                        SpinBox {
                            id: filterValueR
                            height: 25
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
                            height: 25
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
                            height: 25
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
                            height: 25
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
                            id: periodicSendType
                            height: 25
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
                            id:periodicSendTime
                            height: 25
                        }
                        Label {
                            text: "Мин. значение уровня (0-1023):"
                        }
                        SpinBox {
                            id:minLevelValue
                            height: 25
                            to: 4095
                            from: 0
                            value: 0
                        }
                        Label {
                            text: "Макс.значение уровня (0-4095):"
                        }
                        SpinBox {
                            id:maxLevelValue
                            height: 25
                            to: 4095
                            from: 0
                            value: 0
                        }
                        Label {
                            text: "Параметр в выходном сообщении датчика:"
                        }
                        ComboBox {
                            id: typeOutMessage
                            width: 250
                            height: 25
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
                            height: 25
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
                // errors
                Item {
                    id: errorsItem
                    Column {
                        spacing: 20
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent
                        Button {
                            text: "Считать ошибки"
                            id: readErrors
                            onClicked: {
                                viewController.getCurrentDevErrors()
                            }
                        }

                        Label {
                            id:error1Label
                            text: "Датчик не откалиброван:"
                            property bool error1: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error1Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error2Label
                            text: "Выход за минимальную границу измерения на 10%:"
                            property bool error2: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error2Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error3Label
                            text: "Выход за максимальную границу измерения на 10%:"
                            property bool error3: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error3Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error4Label
                            text: "Частота измерительного генератора 0 Гц:"
                            property bool error4: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error4Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error5Label
                            text: "Ведомый датчик №1 не отвечает:"
                            property bool error5: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error5Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error6Label
                            text: "Ведомый датчик №2 не отвечает:"
                            property bool error6: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error6Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error7Label
                            text: "Ведомый датчик №3 не отвечает:"
                            property bool error7: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error7Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                        Label {
                            id:error8Label
                            text: "Ведомый датчик №4 не отвечает:"
                            property bool error8: false
                            Image {
                                height: 32
                                width: 32
                                anchors.left: parent.right
                                anchors.rightMargin: 20
                                source: error8Label.error1 !== true ? "/new/icons/images/icon/4149.png" : "/new/icons/images/icon/4372.png"
                            }
                        }
                    }
                }
                // masterSlave
                Item {
                    id: masterSlaveItem
                    Column {
                        spacing: 10
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent

                        Label {
                            text: qsTr("Ведущий-ведомый:")
                        }
                    }
                }
                // calibration
                Item {
                    id: tarItem
                    Column {
                        spacing: 10
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.fill: parent

                        Label {
                            text: qsTr("Тарировка:")
                        }
                    }
                }
            }
        }

        Rectangle {
            id:rightTabBarRect
            width: 300
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            TabBar {
                id: rightTabBar
                width: 300
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                currentIndex: rightPanelView.index

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
                    enabled: false
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
            Rectangle {
                id: currnetDataRect
                width: rightTabBarRect.width
                height: rightTabBarRect.height - currentData.height
                color: "#ffffff"
                anchors.topMargin: currentData.height
                anchors.top: parent.top
                anchors.left: parent.left
                clip: true

                SwipeView {
                    id: rightPanelView
                    anchors.fill: parent
                    currentIndex: rightTabBar.currentIndex

                    Item {
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
                                visible: devPropertyProgressTmk24.isReady
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
                    Item {
                        id: slavesItem
                        Column {
                            spacing: 10
                            anchors.topMargin: 20
                            anchors.bottomMargin: 20
                            anchors.rightMargin: 20
                            anchors.leftMargin: 20
                            anchors.fill: parent
                        }
                    }
                    Item {
                        id: logsItem
                        Column {
                            spacing: 20
                            anchors.topMargin: 2
                            anchors.bottomMargin: 2
                            anchors.rightMargin: 2
                            anchors.leftMargin: 2
                            anchors.fill: parent

                            ListView {
                                id: logListView
                                anchors.fill: parent
                                clip: true

                                ScrollBar.vertical: ScrollBar {
                                    id: scrollDeviceList
                                    width: 20
                                }

                                delegate: Item {
                                    id: item
                                    height: 30
                                    width: parent.width

                                    Rectangle {
                                        id: rect
                                        width: item.width - 2
                                        anchors.left: parent.left
                                        anchors.leftMargin: 1
                                        height: item.height
                                        color: colorCode
                                        gradient: Gradient {
                                            GradientStop {
                                                position: 0
                                                color: (model.status == 0 ? ("#BFFfff") : (model.status == 1 ? ("#BFEfff") : (model.status == 2 ? ("#F3Bfff") : ("#F3Bfff"))))
                                            }
                                            GradientStop {
                                                position: 1
                                                color: (model.status == 0 ? ("#BFF3C2") : (model.status == 1 ? ("#BFEFF3") : (model.status == 2 ? ("#F3BFC5") : ("#F3BFC5"))))
                                            }
                                        }
                                        Rectangle {
                                            width: parent.width
                                            anchors.top: messageText.bottom
                                            anchors.topMargin: 5
                                            anchors.left: parent.left
                                            anchors.leftMargin: 1
                                            height: 1
                                            color: "black"
                                        }
                                        Label {
                                            id:messageText
                                            text: model.message
                                            font.bold: false
                                            anchors.left: parent.left
                                            anchors.leftMargin: 10
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                }
                                model: ListModel {
                                    id: logListModel
                                }
                            }
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
            anchors.right: rightTabBarRect.left
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
            anchors.right: rightTabBarRect.left
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
        Row {
            id:row7
            clip: true
            anchors.right: row.left
            anchors.rightMargin: 0
            width: 300
            height: 50
            anchors.top: row5.bottom
            anchors.topMargin: 10
            Button {
                id: lButtonSettingsRead
                text: qsTr("Считать настройки")
                anchors.left: parent.left
                anchors.leftMargin: 20
                onClicked: {
                    viewController.getCurrentDevSettings()
                }
            }
            Button {
                id: lButtonWriteRead
                text: qsTr("Записать настройки")
                anchors.left: lButtonSettingsRead.right
                anchors.leftMargin: 10
                onClicked: {
                    writeSettings()
                }
            }
        }
    }
    BusyIndicator {
        id:waitReadyIndicator
        visible: devPropertyProgressTmk24.isReady ? false : true
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

    Dialog {
        id: messageMinMaxWriteOk
        visible: false
        title: "Задание границ измерения"
        standardButtons: StandardButton.Apply
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: qsTr("Задание границы измерения успешно выполнено")
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }

    Dialog {
        id: messageReadSettingsOk
        visible: false
        title: "Чтение настроек"
        standardButtons: StandardButton.Apply
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: qsTr("Чтение настроек успешно выполнено")
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }

    Dialog {
        id: messageWriteSettingsOk
        visible: false
        title: "Запись настроек"
        standardButtons: StandardButton.Apply
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: qsTr("Запись настроек успешно выполнена")
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }
    Dialog {
        id: messageReadErrorsOk
        visible: false
        title: "Чтение ошибок"
        standardButtons: StandardButton.Apply
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: qsTr("Ошибки считаны успешно")
                color: "navy"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }
}
