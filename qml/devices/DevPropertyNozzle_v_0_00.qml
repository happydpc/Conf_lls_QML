import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4 as Controls_1_4
import QtQuick.Controls.Styles 1.4
import CustomControls 1.0
import QtGraphicalEffects 1.0
import "qrc:/qml/miscElems" as MiscElems
import "qrc:/qml/devices" as Devices

Rectangle {
    visible: true
    clip: true

    property bool devIsConnected: false
    property bool devIsReady: false
    property string id: ""

    function setConnected() {
        devIsConnected = true
        devIsReady = false
        setWriteSettingsIsNoAvailable()
    }

    function setDisconnected() {
        devIsConnected = true
        devIsReady = false
        setWriteSettingsIsNoAvailable()
    }

    function setReady() {
        devIsConnected = true
        devIsReady = true
        setWriteSettingsIsAvailable()
    }

    function setPropertyes(keys, values) {
        parseInputData(keys, values)
    }

    function setInitProperty(devKeyProperty, devValueProperty) {
        for(var i=0; i<devKeyProperty.length; i++) {
            if(devKeyProperty[i] === "id") {
                id = devValueProperty[i]
            }
        }
    }

    function removeAll() {

    }

    function getId() {
        return id;
    }

    function setWriteSettingsIsAvailable() {
        writeSettingsButton_1.enabled = true
        writeSettingsButton_2.enabled = true
    }

    function setWriteSettingsIsNoAvailable() {
        writeSettingsButton_1.enabled = false
        writeSettingsButton_2.enabled = false
    }

    function setDevProperty() {
        var keys = viewController.getCurrentDevPropertyKey()
        var values = viewController.getCurrentDevPropertyValue()
        parseInputData(keys, values)
    }

    function insertPeriodicData(keys, values) {

    }

    function setCustomCommandExecuted(keys, args, ackMessageIsVisible) {
        switch(keys[0]) {
        case "getOtherData" :
            parseInputData(keys, args)
            break;
        case "getAccelData" :
            parseInputData(keys, args)
            break;
        case "getNetworkData":
            parseInputData(keys, args)
            break;
            // it last command to read the settings
        case "getNetworkConfig":
            parseInputData(keys, args)
            break;
        case "getAccelConfig":
            parseInputData(keys, args)
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно считаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break;
        case "getCardProperty":
            parseInputData(keys, args)
            break;
        case "getBatteryProperty":
            parseInputData(keys, args)
            break;
        case "setNetworkPassword":
        case "setAccelConfig":
        case "setAccelUseCurrentValuesAsNullPoint":
        case "setNetworkConfig":
        case "setBatteryNewAccum":
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно записаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break
        default: break;
        }
    }

    function parseInputData(keys, values) {
        for(var i=0; i<keys.length; i++) {
            if(keys[i] === "devTypeName") {
                typeDeviceText.text = values[i]
            } else if(keys[i] === "serialNum") {
                snText.text = values[i]
            } else if(keys[i] === "versionFirmare") {
                versionFirmwareText.text = values[i]
            }  else if(keys[i] === "accelX"){
                accelXProgressBar.value = parseInt(values[i])
            }
            if(keys[i] === "accelY"){
                accelYProgressBar.value = parseInt(values[i])
            }
            if(keys[i] === "accelZ"){
                accelZProgressBar.value = parseInt(values[i])
            } else if(keys[i] === "accelConfX") {
                accelCoefX.text = values[i]
            }
            if(keys[i ]=== "accelConfY") {
                accelCoefY.text = values[i]
            }
            if(keys[i] === "accelConfZ") {
                accelCoefZ.text = values[i]
            }
            if(keys[i] === "accelAngle") {
                accelAngle.text = values[i]
            } else if(keys[i] === "networkCurrentIp"){
                networkCurrentIp.text = values[i]
            } else if(keys[i] === "rssiValue") {
                chartRssiValue.dataList.push(values[i])
                chartRssiLines.clear();
                chartRssiValue.graphLength = chartRssiValue.dataList.length
                chartRssiValue.graphAmplitudeMax = 0
                for(var i=0; i<chartRssiValue.dataList.length; i++) {
                    if(chartRssiValue.dataList[i] > chartRssiValue.graphAmplitudeMax) {
                        chartRssiValue.graphAmplitudeMax = chartRssiValue.dataList[i];
                    }
                    if(chartRssiValue.dataList[i] < chartRssiValue.graphAmplitudeMin) {
                        chartRssiValue.graphAmplitudeMin = chartRssiValue.dataList[i];
                    }
                }
                for(i=0; i<chartRssiValue.dataList.length; i++) {
                    chartRssiLines.append(i, chartRssiValue.dataList[i]);
                }
                if(chartRssiValue.dataList.length > 50) {
                    chartRssiValue.dataList.pop()
                }
            } else if(keys[i] === "networkPassword"){
                networkPassword.text = values[i]
            } else if(keys[i] === "powerVoltage"){
                batteryVoltage.value = parseFloat(values[i])
            }
            if(keys[i] === "powerCurrentResouresAvailable"){
                batteryResourseAvailable.value = parseFloat(values[i])
            }
            if(keys[i] === "powerCurrent"){
                batteryCurrent_mA.value = parseFloat(values[i])
            } else if(keys[i] === "cardNumber"){
                cardNumber.text = values[i].toUpperCase()
            }
        }
    }

    function addLogMessage(codeMessage, message) {
        if(devMessageLog.length > 4096) {
            devMessageLog.remove(0, 512)
        }
        if(devMessageAutoScrollSwitch.checked) {
            if(codeMessage === 0) {
                devMessageLog.append(message)
                devMessageLog.cursorPosition = devMessageLog.length-1
            }
        } else {
            var cursorPosition = devMessageLog.cursorPosition
            devMessageLog.append(message)
        }
    }

    function writeNetworkConfig() {
        var keys = [];
        var values = [];
        keys.push("networkPassword")
        values.push(networkPassword.text)
        viewController.setCurrentDevCustomCommand("set current dev settings net config", keys, values)
    }

    Rectangle {
        id: devPropertyProgressTmk24
        property bool isReady: true
        anchors.fill: parent
        color: "#ffffff"
        Rectangle {
            id: barup
            color: "#ffffff"
            height: 50
            anchors.left: parent.left
            anchors.right: parent.right

            TabBar {
                id: tabProperty
                height: 25
                anchors.left: barup.left
                anchors.leftMargin: 30
                anchors.top: barup.top
                anchors.topMargin: 20
                spacing: 5
                currentIndex: devStackParam.currentIndex
                font.pointSize: 8

                MiscElems.TabButtonUp {
                    name: "Текущее состояние"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF274  "
                }
                MiscElems.TabButtonUp {
                    name: "Журнал"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF54A  "
                }
                MiscElems.TabButtonUp {
                    name: "Настройка"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF54A  "
                }
            }
        }

        Rectangle {
            id:spacerList
            anchors.top: barup.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.right: parent.right
            width: parent.width
            height: 2
            color: "#f0f3f6"
        }

        SwipeView {
            id: devStackParam
            anchors.top: spacerList.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            currentIndex: tabProperty.currentIndex

            Item {
                ScrollView {
                    clip: true
                    anchors.fill: parent
                    Column {
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        spacing: 10
                        Row {
                            id:currentDataTexted
                            spacing: 10
                            Row {
                                id:currentDataTexted_1
                                clip: true
                                width: 250
                                height: 25
                                spacing: 10
                                Label {
                                    id: lSn
                                    text: qsTr("Завод/ном:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                TextField {
                                    id: snText
                                    text: qsTr("")
                                    width: parent.width - lSn.width - 15
                                    height: parent.height
                                    enabled: devIsConnected
                                    readOnly: true
                                }
                            }
                            Row {
                                id: currentDataTexted_2
                                clip: true
                                width: 250
                                height: 25
                                spacing: 10
                                Label {
                                    id: lTypeDevice
                                    text: qsTr("Тип датчика:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                TextField {
                                    id: typeDeviceText
                                    text: qsTr("")
                                    width: parent.width - lTypeDevice.width - 15
                                    readOnly: true
                                    enabled: devIsConnected
                                    height: parent.height
                                }
                            }

                            Row {
                                id: currentDataTexted_3
                                clip: true
                                width: 250
                                height: 25
                                spacing: 10
                                Label {
                                    id: lversionFirmwareText
                                    text: qsTr("Версия ПО:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                TextField {
                                    id: versionFirmwareText
                                    text: qsTr("")
                                    enabled: devIsConnected
                                    width: parent.width - lversionFirmwareText.width - 15
                                    readOnly: true
                                    height: parent.height
                                }
                            }
                        }

                        Column {
                            id: column
                            spacing: 5
                            Row {
                                spacing: 10
                                Rectangle {
                                    width: 150
                                    height: 150

                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: batteryVoltageLabel
                                        text: qsTr("Напряжение:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id: batteryVoltage
                                        anchors.centerIn: parent
                                        width: 100
                                        height: 100
                                        penStyle: Qt.RoundCap
                                        dialType: RadialBar.FullDial
                                        progressColor: "#05fff0"
                                        foregroundColor: "transparent"
                                        dialWidth: 15
                                        startAngle: 180
                                        spanAngle: 70
                                        minValue: 0
                                        maxValue: 4.2
                                        value: 0
                                        textFont {
                                            family: "Halvetica"
                                            italic: false
                                            pointSize: 12
                                        }
                                        textColor: "#888d91"
                                        showText: false
                                        suffixText: ""
                                        onValueChanged: {
                                            batteryVoltageCustomText.text = value.toFixed(2) + "V"
                                        }
                                        Text {
                                            id:batteryVoltageCustomText
                                            text:"NA"
                                            color: parent.textColor
                                            font.pointSize: (text.length > 6) ? (parent.textFont.pointSize) : (14)
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                }

                                Rectangle {
                                    id: cardRectangle
                                    width: 200
                                    height: 150

                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        text: qsTr("Карта")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }

                                    TextField {
                                        id: cardNumber
                                        text: qsTr("")
                                        placeholderText: "номер карты"
                                        readOnly: true
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        width: parent.width -10
                                        height: 30
                                    }
                                }

                                Rectangle {
                                    id: networkRectangle
                                    width: 200
                                    height: 150

                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        text: qsTr("Сеть")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }

                                    TextField {
                                        id: networkCurrentIp
                                        text: qsTr("")
                                        width: parent.width -10
                                        height: 30
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        placeholderText: "ip адрес"
                                        readOnly: true
                                    }
                                }

                                Rectangle {
                                    width: 250
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: levelTempLabel1
                                        color: "#888d91"
                                        text: qsTr("Акселерометр:")
                                    }

                                    Column {
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        spacing: 10
                                        Row {
                                            spacing: 10
                                            Label {
                                                text: "X:"
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                            ProgressBar {
                                                id: accelXProgressBar
                                                to: 20000
                                                from: -20000
                                                width: 200
                                                height: 20
                                                value: 0
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                        }
                                        Row {
                                            spacing: 10
                                            Label {
                                                text: "Y:"
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                            ProgressBar {
                                                id: accelYProgressBar
                                                to: 20000
                                                from: -20000
                                                width: 200
                                                value: 0
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                        }

                                        Row {
                                            spacing: 10
                                            Label {
                                                text: "Z:"
                                                anchors.verticalCenter: parent.verticalCenter
                                            }
                                            ProgressBar {
                                                id: accelZProgressBar
                                                to: 20000
                                                from: -20000
                                                width: 200
                                                anchors.verticalCenter: parent.verticalCenter
                                                value: 0
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Column {
                            width: 470
                            height: 250
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            Row{
                                spacing: 10
                                Rectangle {
                                    width:  batCurrentRectangle.width
                                    height: batResourseRectangle.height * 2
                                    Column {
                                        spacing: 10
                                        Rectangle {
                                            id:batResourseRectangle
                                            width: 150
                                            height: 150

                                            radius: 15
                                            color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                            Label {
                                                id: levelCntLabel
                                                text: qsTr("Ресурс батареи:")
                                                anchors.left: parent.left
                                                color: "#888d91"
                                                anchors.leftMargin: 15
                                                anchors.right: parent.right
                                                anchors.rightMargin: 0
                                            }
                                            RadialBar {
                                                id: batteryResourseAvailable
                                                anchors.centerIn: parent
                                                width: 100
                                                height: 100
                                                penStyle: Qt.RoundCap
                                                dialType: RadialBar.FullDial
                                                progressColor: "#b254c6"
                                                foregroundColor: "transparent"
                                                dialWidth: 15
                                                startAngle: 180
                                                spanAngle: 70
                                                minValue: 0
                                                maxValue: 9999
                                                value: 0
                                                textFont {
                                                    family: "Halvetica"
                                                    italic: false
                                                    pointSize: 12
                                                }
                                                textColor: "#888d91"
                                                enabled: devIsConnected
                                                showText: false
                                                suffixText: ""
                                                onValueChanged: {
                                                    batteryResouseAvailableCustomText.text = value.toFixed(0) + "mA"
                                                }
                                                Text {
                                                    id:batteryResouseAvailableCustomText
                                                    text:"NA"
                                                    color: parent.textColor
                                                    font.pointSize: (text.length > 6) ? (parent.textFont.pointSize) : (14)
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                            }
                                        }
                                        Rectangle {
                                            id:batCurrentRectangle
                                            width: 150
                                            height: 150

                                            radius: 15
                                            color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                            Label {
                                                text: qsTr("Ток:")
                                                anchors.left: parent.left
                                                color: "#888d91"
                                                anchors.leftMargin: 15
                                                anchors.right: parent.right
                                                anchors.rightMargin: 0
                                            }
                                            RadialBar {
                                                id: batteryCurrent_mA
                                                anchors.centerIn: parent
                                                width: 100
                                                height: 100
                                                penStyle: Qt.RoundCap
                                                dialType: RadialBar.FullDial
                                                progressColor: "#c6b554"
                                                foregroundColor: "transparent"
                                                dialWidth: 15
                                                startAngle: 180
                                                spanAngle: 70
                                                minValue: 0
                                                maxValue: 9999
                                                value: 1
                                                textFont {
                                                    family: "Halvetica"
                                                    italic: false
                                                    pointSize: 12
                                                }
                                                textColor: "#888d91"
                                                enabled: devIsConnected
                                                showText: false
                                                suffixText: ""
                                                onValueChanged: {
                                                    batteryCurrentCustomText.text = value.toFixed(0) + "mA"
                                                }
                                                Text {
                                                    id:batteryCurrentCustomText
                                                    text:"NA"
                                                    color: parent.textColor
                                                    font.pointSize: (text.length > 6) ? (parent.textFont.pointSize) : (14)
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                            }
                                        }
                                    }
                                }

                                Rectangle {
                                    id: rectangle
                                    height: 310
                                    width: 750
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    ChartView {
                                        id: chartRssiValue
                                        theme: ChartView.ChartThemeLight
                                        title: "RSSI"
                                        antialiasing: true
                                        property int graphLength: 1
                                        property int graphAmplitudeMax: 1
                                        property int graphAmplitudeMin: 1
                                        anchors.fill: parent
                                        property var dataList: []
                                        backgroundColor: devIsConnected ? "#ffffff" : "#d9d9d9"
                                        ValueAxis {
                                            id: chartRssiAxisX
                                            min: 0
                                            max: chartRssiValue.graphLength
                                            tickCount: 5
                                            labelsVisible: false
                                        }
                                        ValueAxis {
                                            id: chartRssiAxisY
                                            min: chartRssiValue.graphAmplitudeMin
                                            max: chartRssiValue.graphAmplitudeMax
                                            tickCount: 5
                                        }
                                        LineSeries {
                                            id: chartRssiLines
                                            axisX: chartRssiAxisX
                                            axisY: chartRssiAxisY
                                        }
                                        enabled: devIsConnected
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Item {
                clip: true
                ScrollView {
                    id:devMessageLogScroll
                    anchors.fill: parent
                    TextArea {
                        id: devMessageLog
                        placeholderText: "Сообщения"
                        height: parent.height
                        width: parent.width
                        wrapMode: TextEdit.Wrap
                    }
                }

                Row {
                    id: rowRow
                    spacing: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 200
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    Switch {
                        id:devMessageAutoScrollSwitch
                        checked: true
                    }
                    Text {
                        id:devMessageAutoScrollComment
                        width: rowRow.width - rowRow.spacing - devMessageAutoScrollSwitch.width
                        height: devMessageAutoScrollSwitch.height
                        verticalAlignment: Text.AlignVCenter
                        text: devMessageAutoScrollSwitch.checked ? "Автопрокрутка\nвкл" : "Автопрокрутка\nвыкл"
                    }
                }
            }

            Item {
                clip: true
                Column {
                    anchors.fill: parent
                    Rectangle {
                        id: subBarup
                        color: "#fdfdfb"
                        height: 45
                        width: parent.width
                        TabBar {
                            id:tabSubProperty
                            height: 25
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.topMargin: 17
                            anchors.leftMargin: 30
                            spacing: 5
                            currentIndex: stackSubProperty.currentIndex
                            font.pointSize: 8
                            background: Rectangle {
                                color: "#ffffff"
                            }
                            MiscElems.TabButtonUp {
                                name: "Акселерометр"
                                textLine: 1
                                widthBody: 130
                                useIcon: true
                                iconCode: "\uF14E  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Сеть"
                                textLine: 1
                                widthBody: 120
                                useIcon: true
                                iconCode: "\uF0C1  "
                            }
                            MiscElems.TabButtonUp {
                                name: "  Питание"
                                textLine: 1
                                useIcon: true
                                widthBody: 130
                                iconCode: "\uF241  "
                            }
                        }
                    }

                    SwipeView {
                        id: stackSubProperty
                        currentIndex: tabSubProperty.currentIndex
                        clip: true
                        height: parent.height - subBarup.height
                        width: parent.width
                        Item {
                            id: currentStackData
                            ScrollView {
                                clip: true
                                anchors.fill: parent
                                Column {
                                    spacing: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 15
                                    anchors.left: parent.left
                                    anchors.leftMargin: 15
                                    Row {
                                        width: 500
                                        height: 100
                                        Rectangle {
                                            id: accelCoefRect
                                            width: 500
                                            height: 250
                                            color: "#fdfdfb"
                                            Column {
                                                id: column3
                                                anchors.top: parent.top
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 10
                                                Label {
                                                    text: "Коэффициенты:"
                                                }
                                                Label {
                                                    text: "X:"
                                                }
                                                TextField {
                                                    id: accelCoefX
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                                Label {
                                                    text: "Y:"
                                                }
                                                TextField {
                                                    id: accelCoefY
                                                    height: 30
                                                    width: 300
                                                }
                                                Label {
                                                    text: "Z:"
                                                }
                                                TextField {
                                                    id: accelCoefZ
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                                Label {
                                                    text: "Угол\nотклонения:"
                                                }
                                                TextField {
                                                    id: accelAngle
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                        }
                                        Column {
                                            Button {
                                                id: insertCurrentAccelValues
                                                width: 180
                                                height: 70
                                                text: "Использовать\nтекущие\nзначения"
                                                enabled: devIsConnected
                                                onClicked: {
                                                    accelCoefX.text = accelXProgressBar.value.toString()
                                                    accelCoefY.text = accelYProgressBar.value.toString()
                                                    accelCoefZ.text = accelZProgressBar.value.toString()
                                                }
                                            }
                                            Button {
                                                id: readSetingsButton_1
                                                width: 180
                                                height: 50
                                                text: "Считать настройки"
                                                enabled: devIsConnected
                                                onClicked: {
                                                    viewController.setCurrentDevCustomCommand("get current dev settings")
                                                }
                                            }
                                            Button {
                                                id: writeSettingsButton_1
                                                width: 180
                                                height: 50
                                                text: "Записать настройки"
                                                onClicked: {
                                                    var keys = [];
                                                    var values = [];
                                                    keys.push("accelConfX")
                                                    values.push(accelCoefX.text)
                                                    keys.push("accelConfY")
                                                    values.push(accelCoefY.text)
                                                    keys.push("accelConfZ")
                                                    values.push(accelCoefZ.text)
                                                    keys.push("accelAngle")
                                                    values.push(accelAngle.text)
                                                    viewController.setCurrentDevCustomCommand("set current dev settings accel config", keys, values)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Item {
                            ScrollView {
                                clip: true
                                anchors.fill: parent
                                Column {
                                    spacing: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 15
                                    anchors.left: parent.left
                                    anchors.leftMargin: 15
                                    Row {
                                        width: 500
                                        height: 100
                                        Rectangle {
                                            id: networlSettingsCoefRect
                                            width: 500
                                            height: 80
                                            color: "#fdfdfb"
                                            Column{
                                                anchors.top: parent.top
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 5
                                                Label {
                                                    text: "Пароль:"
                                                }
                                                TextField {
                                                    id: networkPassword
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                        }
                                        Column{
                                            Button {
                                                id: readSetingsButton_2
                                                width: 180
                                                height: 50
                                                text: "Считать настройки"
                                                enabled: devIsConnected
                                                onClicked: {
                                                    viewController.setCurrentDevCustomCommand("get current dev settings")
                                                }
                                            }
                                            Button {
                                                id: writeSettingsButton_2
                                                width: 180
                                                height: 50
                                                text: "Записать настройки"
                                                onClicked: {
                                                    writeNetworkConfig()
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Item {
                            id: settingsBattery
                            ScrollView {
                                anchors.fill: parent
                                clip: true
                                Column {
                                    spacing: 10
                                    anchors.top: parent.top
                                    clip: true
                                    Rectangle {
                                        id: networlBatteryRect
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Button {
                                            id: batterySetNewAccumulate
                                            height: 30
                                            width: 200
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.leftMargin: 15
                                            anchors.left: parent.left
                                            text: "Новая батарея"
                                            onClicked: {
                                                var keys = []
                                                var values = []
                                                viewController.setCurrentDevCustomCommand("set new battery", keys, values)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: dialogInfoMessage
        visible: false
        title: ""
        property string message: ""
        standardButtons: StandardButton.Ok
        Rectangle {
            color: "transparent"
            implicitWidth: 500
            implicitHeight: 50
            Text {
                text: dialogInfoMessage.message
                color: "black"
                anchors.centerIn: parent
            }
        }
        onAccepted: {
            close()
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 20
        property string message: "Ожидание ответа..."
        visible: ((devIsConnected) && (devIsReady)) ? false : true
        width: 350
        height: 200
        BusyIndicator {
            id:waitReadyIndicator
            width: 110
            height: 110
        }
        Label {
            text: parent.message
        }
    }
}
