import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4 as ControlOld
import QtQuick.Controls.Styles 1.4

Rectangle {
    color: "#e7e9eb"
    anchors.fill: parent

    property alias messageMinMaxWriteOk: messageMinMaxWriteOk
    property alias messageReadSettingsOk: messageReadSettingsOk
    property alias messageWriteSettingsOk: messageWriteSettingsOk
    property alias messageReadErrorsOk: messageReadErrorsOk
    property alias messageReadTarTableOk: messageReadTarTableOk

    function setNoReady() {
        devPropertyProgressTmk24.isReady = false
        //        devPropertyProgressTmk24.isReady = true
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
        currentChartLines.clear();
        graph.graphLength = list.length
        graph.graphAmplitudeMax = 0
        for(var i=0; i<list.length; i++) {
            if(graph.graphAmplitudeMax < parseInt(list[i])) {
                graph.graphAmplitudeMax = parseInt(list[i]);
            }
        }
        for(i=0; i<list.length; i++) {
            currentChartLines.append(i, parseInt(list[i]));
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
        masterSlaveModes.currentIndex = settings[14]
        baudrateRs232Values.currentIndex = settings[15] //        ret << QString::number(lls_data.settings.get.value.rs232Speed);
        baudrateRs485Values.currentIndex = settings[16]//        ret << QString::number(lls_data.settings.get.value.rs485Speed);
        masterSlaveFullCountes.value = settings[17]//        ret << QString::number(lls_data.settings.get.value.slaveCount);
        masterSlaveSlaveId_1.value = settings[18] //        ret << QString::number(lls_data.settings.get.value.slaveAddr[0]);
        masterSlaveSlaveId_2.value = settings[19] //        ret << QString::number(lls_data.settings.get.value.slaveAddr[1]);
        masterSlaveSlaveId_3.value = settings[20] //        ret << QString::number(lls_data.settings.get.value.slaveAddr[2]);
        masterSlaveSlaveId_4.value = settings[21] //        ret << QString::number(lls_data.settings.get.value.slaveAddr[3]);
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
        settings.push(masterSlaveModes.currentIndex)
        settings.push(baudrateRs232Values.currentIndex) //        ret << QString::number(lls_data.settings.get.value.rs232Speed);
        settings.push(baudrateRs485Values.currentIndex)//        ret << QString::number(lls_data.settings.get.value.rs485Speed);
        settings.push(masterSlaveFullCountes.value)//        ret << QString::number(lls_data.settings.get.value.slaveCount);
        settings.push(masterSlaveSlaveId_1.value) //        ret << QString::number(lls_data.settings.get.value.slaveAddr[0]);
        settings.push(masterSlaveSlaveId_2.value) //        ret << QString::number(lls_data.settings.get.value.slaveAddr[1]);
        settings.push(masterSlaveSlaveId_3.value) //        ret << QString::number(lls_data.settings.get.value.slaveAddr[2]);
        settings.push(masterSlaveSlaveId_4.value) //        ret << QString::number(lls_data.settings.get.value.slaveAddr[3]);
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
    function remakeTarTableChart() {
        chartTarTableLine.clear()
        var tarArrayLevel = [];
        var tarArrayValue = [];
        var maxLevel = 0;
        var maxValue = 0;
        for(var i=0; i<tarTabView.rowCount; i++) {
            var item = tarTabView.model.get(i)
            tarArrayLevel.push(item.Level)
            tarArrayValue.push(item.Value)
            if(maxLevel < item.Level) {
                maxLevel = item.Level
            }
            if(maxValue < item.Value) {
                maxValue = item.Value
            }
            console.log("Value =" + item.Value + "\nLevel=" + item.Level)
        }
        chartTarTable.chartTarTableAmplitudeMax = parseInt(maxLevel)
        chartTarTable.chartTarTableLength = parseInt(maxValue)
        console.log("MaxLevel =" + chartTarTable.chartTarTableAmplitudeMax)
        for(i=0; i<chartTarTable.chartTarTableLength; i++) {
            chartTarTableLine.append(parseInt(tarArrayValue[i]), parseInt(tarArrayLevel[i]));
            console.log("Add=" + i + " " + tarArrayLevel[i])
        }
    }

    function writeTarTable() {
        var tarArrayLevel = [];
        var tarArrayValue = [];
        for(var i=0; i<tarTabView.rowCount; i++) {
            var item = tarTabView.model.get(i)
            tarArrayLevel.push(item.Level)
            tarArrayValue.push(item.Value)
        }
        viewController.setCurrentDevTarTable(tarArrayLevel,tarArrayValue)
    }

    function readTarTable(table) {
        tarTabView.model.clear()
        var stepCounter = 0;
        var level = 0;
        var value = 0;
        for(var i=0; i<table.length; i++) {
            if(stepCounter == 0) {
                stepCounter++;
                value = table[i]
            } else {
                level = table[i]
                stepCounter = 0;
                tarTableListModel.append({"Value":parseInt(value),"Level":parseInt(level)})
            }
        }
        timerAffterRefrashTarTable.start()
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
                text: qsTr("Ведущий\nведомый")
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
            id:properiesViewRect
            anchors.top: propertiesTabBar.bottom
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: (rightPanelView.width + 10)
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            color: "transparent"
            SwipeView {
                id: propertiesView
                anchors.fill: properiesViewRect
                currentIndex: propertiesTabBar.currentIndex
                clip: true

                onCurrentIndexChanged: {
                    if(propertiesView.currentItem == errorsItem) {
                        viewController.getCurrentDevErrors()
                    }
                    if(propertiesView.currentItem == tarItem) {
                        //                        viewController.getCurrentDevTarTable()
                    }
                }

                // 1- calibration
                Item {
                    id: calibrationItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Column {
                            spacing: 10
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
                }
                // 2- filtration
                Item {
                    id: filtrationItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Column {
                            spacing: 10
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
                }
                // 3- temperature
                Item {
                    id: tempCompensationItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Column {
                            spacing: 10
                            Label {
                                text: qsTr("Температурная компенсация линейного расширения топлива")
                                anchors.left: parent.left
                                anchors.right: parent.right
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
                }
                // base parameters
                Item {
                    id: basePropertiesItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Column {
                            spacing: 10

                            Button {
                                text: "Сменить сетевой адрес"
                                id: changeIdAddr
                                anchors.left: parent.left
                                anchors.right: parent.right
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
                            Label {
                                text: "Скорость обмена:"
                                id: baudrateLabel
                            }
                            Label {
                                text: "По RS232:"
                                id: baudrateRs232Label
                            }
                            ComboBox {
                                id: baudrateRs232Values
                                height: 25
                                model: ListModel {
                                    ListElement {
                                        text: "2800"
                                    }
                                    ListElement {
                                        text: "4800"
                                    }
                                    ListElement {
                                        text: "9600"
                                    }
                                    ListElement {
                                        text: "19200"
                                    }
                                    ListElement {
                                        text: "28800"
                                    }
                                    ListElement {
                                        text: "38400"
                                    }
                                    ListElement {
                                        text: "57600"
                                    }
                                    ListElement {
                                        text: "115200"
                                    }
                                }
                            }
                            Label {
                                text: "По RS485:"
                                id: baudrateRs485Label
                            }

                            ComboBox {
                                id: baudrateRs485Values
                                height: 25
                                model: ListModel {
                                    ListElement {
                                        text: "2800"
                                    }
                                    ListElement {
                                        text: "4800"
                                    }
                                    ListElement {
                                        text: "9600"
                                    }
                                    ListElement {
                                        text: "19200"
                                    }
                                    ListElement {
                                        text: "28800"
                                    }
                                    ListElement {
                                        text: "38400"
                                    }
                                    ListElement {
                                        text: "57600"
                                    }
                                    ListElement {
                                        text: "115200"
                                    }
                                }
                            }
                        }
                    }
                }
                // errors
                Item {
                    id: errorsItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Column {
                            spacing: 20
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
                }
                // masterSlave
                Item {
                    id: masterSlaveItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Rectangle{
                            id:masterSlaveRect
                            width: propertiesView.width
                            height: properiesViewRect.height
                            color: "transparent"

                            Row {
                                id: masterSlaveRow
                                anchors.fill: masterSlaveRect
                                Rectangle {
                                    id: rectangle1
                                    width: masterSlaveRect.width / 2
                                    color: "transparent"
                                    anchors.bottom: parent.bottom
                                    anchors.top: parent.top
                                    Label {
                                        id: masterSlaveModeLabel
                                        text: "Режим ведущий/ведомый:"
                                    }
                                    ComboBox {
                                        id: masterSlaveModes
                                        anchors.top: masterSlaveModeLabel.bottom
                                        anchors.topMargin: 5
                                        height: 25
                                        model: ListModel {
                                            ListElement {
                                                text: "Выключен"
                                            }
                                            ListElement {
                                                text: "Ведомый"
                                            }
                                            ListElement {
                                                text: "Ведущий"
                                            }
                                            ListElement {
                                                text: "Трансляция"
                                            }
                                        }
                                        onCurrentIndexChanged: {
                                            if(masterSlaveModes.currentIndex == 2) {
                                                masterSlavesAddresRectange.enabled = true
                                            } else {
                                                masterSlavesAddresRectange.enabled = false
                                                masterSlaveFullCountes.value = 0
                                            }
                                        }
                                    }
                                }
                                Rectangle {
                                    id: masterSlavesAddresRectange
                                    width: masterSlaveRect.width / 2
                                    color: "transparent"
                                    anchors.bottom: parent.bottom
                                    anchors.top: parent.top
                                    Label {
                                        id: masterSlaveModeCountAllLabel
                                        text: "Количество ведомых:"
                                        anchors.topMargin: 20
                                    }
                                    SpinBox {
                                        id: masterSlaveFullCountes
                                        height: 25
                                        anchors.top: masterSlaveModeCountAllLabel.bottom
                                        from: 0
                                        to: 4
                                        onValueChanged: {
                                            if(masterSlaveFullCountes.value >= 1) {
                                                masterSlaveSlaveId_1.enabled = true
                                            } else {
                                                masterSlaveFullCountes.value = 0
                                                masterSlaveModes.currentIndex = 0
                                                masterSlaveSlaveId_1.enabled = false
                                                masterSlaveSlaveId_2.enabled = false
                                                masterSlaveSlaveId_3.enabled = false
                                                masterSlaveSlaveId_4.enabled = false
                                            }
                                            if(masterSlaveFullCountes.value >= 2) {
                                                masterSlaveSlaveId_2.enabled = true
                                            } else {
                                                masterSlaveSlaveId_2.enabled = false
                                            }
                                            if(masterSlaveFullCountes.value >= 3) {
                                                masterSlaveSlaveId_3.enabled = true
                                            } else {
                                                masterSlaveSlaveId_3.enabled = false
                                            }
                                            if(masterSlaveFullCountes.value >= 4) {
                                                masterSlaveSlaveId_4.enabled = true
                                            } else {
                                                masterSlaveSlaveId_4.enabled = false
                                            }
                                        }
                                    }
                                    Label {
                                        text: "Адрес ведомого №1"
                                        id: masterSlaveAddress_1
                                        anchors.top: masterSlaveFullCountes.bottom
                                        anchors.topMargin: 15
                                    }
                                    SpinBox {
                                        id: masterSlaveSlaveId_1
                                        from: 1
                                        to: 254
                                        height: 25
                                        anchors.top: masterSlaveAddress_1.bottom
                                    }
                                    Label {
                                        text: "Адрес ведомого №2"
                                        id: masterSlaveAddress_2
                                        anchors.top: masterSlaveSlaveId_1.bottom
                                        anchors.topMargin: 5
                                    }
                                    SpinBox {
                                        id: masterSlaveSlaveId_2
                                        height: 25
                                        from: 1
                                        to: 254
                                        anchors.top: masterSlaveAddress_2.bottom
                                    }
                                    Label {
                                        text: "Адрес ведомого №3"
                                        id: masterSlaveAddress_3
                                        anchors.top: masterSlaveSlaveId_2.bottom
                                        anchors.topMargin: 5
                                    }
                                    SpinBox {
                                        id: masterSlaveSlaveId_3
                                        height: 25
                                        from: 1
                                        to: 254
                                        anchors.top: masterSlaveAddress_3.bottom
                                    }
                                    Label {
                                        text: "Адрес ведомого №4"
                                        id: masterSlaveAddress_4
                                        anchors.top: masterSlaveSlaveId_3.bottom
                                        anchors.topMargin: 5
                                    }
                                    SpinBox {
                                        id: masterSlaveSlaveId_4
                                        height: 25
                                        from: 1
                                        to: 254
                                        anchors.top: masterSlaveAddress_4.bottom
                                    }
                                }
                            }
                        }
                    }
                }
                // calibration
                Item {
                    id: tarItem
                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        Rectangle{
                            id:tarTabRect
                            width: propertiesView.width
                            height: parent.height - tarBatButtons.height

                            ControlOld.TableView {
                                id:tarTabView
                                anchors.top: tarTabRect.top
                                anchors.left: tarTabRect.left
                                anchors.bottom: tarTabRect.bottom
                                width: tarTabRect.width / 2
                                ControlOld.TableViewColumn {
                                    id: tableDelegateValue
                                    role: "Value"
                                    title: "Объем"
                                    property int value: model.Value
                                    delegate: Rectangle {
                                        anchors.fill: parent
                                        color: valueInputValue.text.length >0 ? "transparent" : "red"
                                        TextInput {
                                            id:valueInputValue
                                            anchors.fill: parent
                                            selectionColor: "red"
                                            text:(model.Value===0) ? "0" : model.Value
                                            validator: RegExpValidator { regExp: /[0-9A-F]+/ }
                                            onEditingFinished: {
                                                model.Value = text
                                                remakeTarTableChart()
                                            }
                                        }
                                    }
                                }
                                ControlOld.TableViewColumn {
                                    id: tableDelegateLevel
                                    role: "Level"
                                    title: "Уровень"
                                    property int level: model.Level
                                    delegate: Rectangle {
                                        anchors.fill: parent
                                        color: valueInputLevel.text.length >0 ? "transparent" : "red"
                                        TextInput {
                                            id:valueInputLevel
                                            anchors.fill: parent
                                            selectionColor: "red"
                                            text:(model.Level===0) ? "0" : model.Level
                                            validator: RegExpValidator { regExp: /[0-9A-F]+/ }
                                            onEditingFinished: {
                                                model.Level = text
                                                remakeTarTableChart()
                                            }

                                        }
                                    }
                                }
                                model: ListModel {
                                    id: tarTableListModel
                                }
                                onCurrentRowChanged: {
                                    tarTabView.selection.clear()
                                    tarTabView.selection.select(tarTabView.currentRow)
                                }

                                rowDelegate: Rectangle {
                                    SystemPalette {
                                        id: systemPalette
                                        colorGroup: SystemPalette.Active
                                    }
                                    color: {
                                        var baseColor = styleData.alternate ? systemPalette.alternateBase : systemPalette.base
                                        return styleData.selected ? "orange" : baseColor
                                    }
                                }

                            }
                            Rectangle {
                                anchors.top: tarTabRect.top
                                anchors.right: tarTabRect.right
                                anchors.bottom: tarTabRect.bottom
                                height: parent.height
                                width: tarTabRect.width / 2
                                ChartView {
                                    id: chartTarTable
                                    anchors.fill: parent
                                    theme: ChartView.ChartThemeBlueCerulean
                                    clip: true
                                    antialiasing: true
                                    title: "Уровень"
                                    property int chartTarTableLength: 1
                                    property int chartTarTableAmplitudeMax: 1
                                    ValueAxis {
                                        id: chartTarTableAxisX
                                        min: 0
                                        max: chartTarTable.chartTarTableLength
                                        tickCount: 5
                                    }
                                    ValueAxis {
                                        id: chartTarTableAxisY
                                        min: 0
                                        max: chartTarTable.chartTarTableAmplitudeMax
                                        tickCount: 5
                                    }
                                    LineSeries {
                                        id:chartTarTableLine
                                        color: "red"
                                        axisX: chartTarTableAxisX
                                        axisY: chartTarTableAxisY
                                    }
                                }
                            }
                        }
                        Row {
                            id:tarBatButtons
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            spacing: 0
                            Button {
                                id:tarTabAddStep
                                text:"Добавить"
                                height: 50
                                width: 70
                                font.pointSize: 8
                                onClicked: {
                                    tarTableListModel.append({"Value":"0","Level":"0"})
                                    timerAffterRefrashTarTable.start()
                                }
                            }
                            Button {
                                id:tarTabRemoveStep
                                text:"Удалить"
                                font.pointSize: 8
                                height: 50
                                width: 70
                                Dialog {
                                    id: dialogRemoveTarTableRow
                                    visible: false
                                    title: "Удаление записи таблицы"
                                    standardButtons: StandardButton.Apply
                                    Rectangle {
                                        color: "transparent"
                                        implicitWidth: 500
                                        implicitHeight: 50
                                        Text {
                                            text: "Для удаления сначала кликните по удалялемой строке в таблице"
                                            color: "black"
                                            anchors.centerIn: parent
                                        }
                                    }
                                    onApply: {
                                        close()
                                    }
                                }
                                onClicked: {
                                    if(tarTabView.currentRow == -1) {
                                        dialogRemoveTarTableRow.open()
                                        close()
                                    } else {
                                        tarTabView.model.remove(tarTabView.currentRow)
                                        timerAffterRefrashTarTable.start()
                                    }
                                }
                            }
                            Button {
                                id:tarTabCleaarFull
                                text:"Очистить"
                                font.pointSize: 8
                                height: 50
                                width: 70
                                Dialog {
                                    id: dialogClearTarTable
                                    visible: false
                                    title: "Очистка записей таблицы"
                                    standardButtons: StandardButton.Close | StandardButton.Apply
                                    Rectangle {
                                        color: "transparent"
                                        implicitWidth: 500
                                        implicitHeight: 50
                                        Text {
                                            text: "Очистить таблицу\nВы уверены?"
                                            color: "black"
                                            anchors.centerIn: parent
                                        }
                                    }
                                    onApply: {
                                        dialogClearTarTable.open()
                                        var size = tarTabView.rowCount
                                        tarTabView.model.clear()
                                        timerAffterRefrashTarTable.start()
                                        close()
                                    }
                                }
                                onClicked: {
                                    dialogClearTarTable.open()
                                }
                            }
                            Button {
                                id:tarTabReadTable
                                text:"Считать\nтаблицу"
                                font.pointSize: 8
                                width: 70
                                height: 50
                                onClicked: {
                                    dialogReadTarTable.open()
                                }
                                Dialog {
                                    id: dialogReadTarTable
                                    visible: false
                                    title: "Чтение записей таблицы из устройства"
                                    standardButtons: StandardButton.Close | StandardButton.Apply
                                    Rectangle {
                                        color: "transparent"
                                        implicitWidth: 500
                                        implicitHeight: 50
                                        Text {
                                            text: "Считать данные?\nВсе не сохраненные изменения будут утеряны!\nВы уверены?"
                                            color: "black"
                                            anchors.centerIn: parent
                                        }
                                    }
                                    onApply: {
                                        viewController.getCurrentDevTarTable()
                                        close()
                                    }
                                }
                            }
                            Button {
                                id:tarTabWriteTable
                                text:"Записать\nтаблицу"
                                width: 70
                                height: 50
                                font.pointSize: 8
                                Dialog {
                                    id: dialogWriteTarTable
                                    visible: false
                                    title: "Запись таблицы"
                                    standardButtons: StandardButton.Close | StandardButton.Apply
                                    Rectangle {
                                        color: "transparent"
                                        implicitWidth: 500
                                        implicitHeight: 50
                                        Text {
                                            text: "Записать таблицу в устройство!\nВы уверены?"
                                            color: "black"
                                            anchors.centerIn: parent
                                        }
                                    }
                                    onApply: {
                                        writeTarTable()
                                        close()
                                    }
                                }
                                onClicked: {
                                    if(tarTabView.rowCount >0) {
                                        dialogWriteTarTable.open()
                                    }
                                }
                            }
                            Button {
                                id:tarTabTableExport
                                text:"Выгрузить\n.csv"
                                width: 80
                                font.pointSize: 8
                                height: 50

                                FileDialog {
                                    id: dialogExportTarTable
                                    folder: shortcuts.home
                                    selectMultiple: false
                                    selectFolder: false
                                    title: "Save to file"
                                    nameFilters: [ "All files (*)" ]
                                    selectExisting: false
                                    onAccepted: {
                                        if(dialogExportTarTable.selectExisting == true) {
                                            console.log(dialogExportTarTable.fileUrl)
                                        }
                                        else {
                                            console.log(dialogExportTarTable.fileUrl)
                                            console.log("You chose: " + dialogExportTarTable.fileUrls)//--------   (1)
                                            var tarArrayLevel = [];
                                            var tarArrayValue = [];
                                            for(var i=0; i<tarTabView.rowCount; i++) {
                                                var item = tarTabView.model.get(i)
                                                tarArrayLevel.push(item.Level)
                                                tarArrayValue.push(item.Value)
                                            }
                                            viewController.setCurrentDevExportTarTable(dialogExportTarTable.fileUrls, tarArrayLevel,tarArrayValue)
                                        }
                                    }
                                }
                                onClicked: {
                                    dialogExportTarTable.open()
                                }
                            }
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
                                    id: currentChartAxisX
                                    min: 0
                                    max: graph.graphLength
                                    tickCount: 5
                                }
                                ValueAxis {
                                    id: currentChartAxisY
                                    min: 0
                                    max: graph.graphAmplitudeMax
                                    tickCount: 5
                                }
                                LineSeries {
                                    id: currentChartLines
                                    axisX: currentChartAxisX
                                    axisY: currentChartAxisY
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
                                    width: 20
                                }

                                delegate: Item {
                                    id: logItemDelegate
                                    height: 30
                                    width: parent.width

                                    Rectangle {
                                        width: logItemDelegate.width - 2
                                        anchors.left: parent.left
                                        anchors.leftMargin: 1
                                        height: logItemDelegate.height
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
                                            anchors.top: logMessageText.bottom
                                            anchors.topMargin: 5
                                            anchors.left: parent.left
                                            anchors.leftMargin: 1
                                            height: 1
                                            color: "black"
                                        }
                                        Label {
                                            id:logMessageText
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
                color: "black"
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
                color: "black"
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
                color: "black"
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
                color: "black"
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
                color: "black"
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
                color: "black"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }
    Dialog {
        id: messageReadTarTableOk
        visible: false
        title: "Чтение таблицы"
        standardButtons: StandardButton.Apply
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: qsTr("Таблица тарировки успешно записана")
                color: "black"
                anchors.centerIn: parent
            }
        }
        onApply: {
            close()
        }
    }
    Timer {
        id: timerAffterRefrashTarTable
        interval: 100
        running: false
        repeat: false
        onTriggered: {
            remakeTarTableChart()
        }
    }
}
