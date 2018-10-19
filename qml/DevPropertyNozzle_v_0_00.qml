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

Rectangle {
    anchors.fill: parent
    property bool devIsConnected: false

    function setNoReady() {
        devIsConnected = false
        setWriteSettingsIsNoAvailable()
    }
    function setReady() {
        devIsConnected = true
        setWriteSettingsIsAvailable()
    }
    function setResetState() {
        tabProperty.setCurrentIndex(0)
        stackSubProperty.setCurrentIndex(0)
        setNoReady()
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
        for(var i=0; i<keys.length; i++) {
            if(keys[i] === "devTypeName"){
                typeDeviceText.text = values[i]
            }
            if(keys[i] === "serialNum"){
                snText.text = values[i]
            }
            if(keys[i] === "versionFirmare"){
                versionFirmwareText.text = values[i]
            }
        }
    }

    function setCustomCommandExecuted(keys, args, ackMessageIsVisible) {
        var i = 0;
        if(keys.length > 0) {
            devIsConnected = true
        }
        switch(keys[0]) {
        case "getOtherData" :
            for(i=0; i<keys.length; i++) {
                if(keys[i] === "versionFirmare"){
                    versionFirmwareText.text = args[i]
                }
            }
            break;
        case "getAccelData" :
            for(i=0; i<keys.length; i++) {
                if(keys[i] === "accelX"){
                    accelXProgressBar.value = parseInt(args[i])
                }
                if(keys[i] === "accelY"){
                    accelYProgressBar.value = parseInt(args[i])
                }
                if(keys[i] === "accelZ"){
                    accelZProgressBar.value = parseInt(args[i])
                }
            }
            break;
        case "getNetworkData":
            for(i=0; i<keys.length; i++) {
                if(keys[i] === "networkCurrentIp"){
                    networkCurrentIp.text = args[i]
                }
                if(keys[i] === "rssiValue") {
                    chartRssiValue.dataList.push(args[i])
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
                }
            }
            break;
            // it last command to read the settings
        case "getNetworkConfig":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "networkpassword"){
                    networkPassword.text = args[i]
                }
            }
            break;
        case "getAccelConfig":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "accelconfx") {
                    accelCoefX.text = args[i]
                }
                if(keys[i].toLowerCase() === "accelconfy") {
                    accelCoefY.text = args[i]
                }
                if(keys[i].toLowerCase() === "accelconfz") {
                    accelCoefZ.text = args[i]
                }
                if(keys[i].toLowerCase() === "accelAngle") {
                    accelCoeDeltaX.text = args[i]
                }
            }
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно считаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break;
        case "getCardProperty":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "cardnumber"){
                    cardNumber.text = args[i].toUpperCase()
                }
            }
            break;
        case "getBatteryProperty":
            for(i=0; i<keys.length; i++) {
                if(keys[i] === "powerVoltage"){
                    batteryVoltage.value = parseFloat(args[i])
                }
                if(keys[i] === "powerCurrentResouresAvailable"){
                    batteryResourseAvailable.value = parseFloat(args[i])
                }
                if(keys[i] === "powerCurrent"){
                    batteryCurrent_mA.value = parseFloat(args[i])
                }
            }
            break;
        case "setNetworkPassword":
        case "setAccelConfig":
        case "setAccelUseCurrentValuesAsNullPoint":
        case "setNetworkConfig":
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно записаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break
        default: break;
        }
    }

    function addLogMessage(codeMessage, message) { // TODO:!!!
        log.append(message)
    }

    function addDeviceLogMessage(message) {
        if(devMessageLog.length > 2048) {
            devMessageLog.remove(0, message.length + 100)
        }
        if(devMessageAutoScrollSwitch.checked) {
            devMessageLog.append(message)
            devMessageLog.cursorPosition = devMessageLog.length-1
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
        viewController.setCurrentDevCustomCommandWithoutAckDialog("set current dev settings net config", keys, values)
    }

    Rectangle {
        id: devProperty
        anchors.fill: parent
        color: "transparent"
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

                TabButtonUp {
                    name: "Текущее состояние"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF274  "
                }
                TabButtonUp {
                    name: "Журнал"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF54A  "
                }
                TabButtonUp {
                    name: "Настройка"
                    textLine: 1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF54A  "
                }
            }
        }

        Rectangle {
            id: spacerList
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
            currentIndex: tabProperty.currentIndex
            anchors.top: spacerList.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onCurrentIndexChanged: {
                if(devStackParam.currentItem == settingsItem) {
                    viewController.getCurrentDevCustomCommand("get current dev settings witout dialog")
                }
            }

            Item {
                ScrollView {
                    clip: true
                    anchors.fill: parent

                    Column {
                        id: column2
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        spacing: 10

                        Row {
                            id: currentDataTexted
                            layer.enabled: true
                            width: 800
                            height: 50
                            Row {
                                id: currentDataTexted_1
                                clip: true
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.top: parent.top
                                anchors.topMargin: 13
                                width: 250
                                height: 25
                                Label {
                                    id: lSn
                                    text: qsTr("Завод/ном:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                TextField {
                                    id: snText
                                    text: qsTr("")
                                    anchors.left: lSn.right
                                    anchors.leftMargin: 5
                                    anchors.right: parent.right
                                    height: parent.height
                                    enabled: devIsConnected
                                    readOnly: true
                                }
                            }

                            Row {
                                id: currentDataTexted_2
                                clip: true
                                anchors.left: currentDataTexted_1.right
                                anchors.leftMargin: 10
                                anchors.top: parent.top
                                anchors.topMargin: 13
                                width: 250
                                height: 25
                                Label {
                                    id: lTypeDevice
                                    text: qsTr("Тип:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                TextField {
                                    id: typeDeviceText
                                    text: qsTr("")
                                    anchors.left: lTypeDevice.right
                                    anchors.right: parent.right
                                    anchors.leftMargin: 5
                                    readOnly: true
                                    enabled: devIsConnected
                                    height: parent.height
                                }
                            }

                            Row {
                                id: currentDataTexted_3
                                clip: true
                                anchors.left: currentDataTexted_2.right
                                anchors.leftMargin: 10
                                anchors.top: parent.top
                                anchors.topMargin: 13
                                width: 250
                                height: 25
                                Label {
                                    id: lversionFirmwareText
                                    text: qsTr("Версия ПО:")
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                TextField {
                                    id: versionFirmwareText
                                    text: qsTr("")
                                    readOnly: true
                                    enabled: devIsConnected
                                    anchors.left: lversionFirmwareText.right
                                    anchors.right: parent.right
                                    anchors.leftMargin: 5
                                    height: parent.height
                                }
                            }
                            layer.effect: DropShadow {
                                transparentBorder: true
                                horizontalOffset: 0
                                verticalOffset: 1
                                color: "#e0e5ef"
                                samples: 10
                                radius: 10
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
                                    layer.enabled: true
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
                                    layer.effect: DropShadow {
                                        transparentBorder: true
                                        horizontalOffset: 0
                                        verticalOffset: 1
                                        color: "#e0e5ef"
                                        samples: 10
                                        radius: 10
                                    }
                                }

                                Rectangle {
                                    id: cardRectangle
                                    width: 200
                                    height: 150
                                    layer.enabled: true
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
                                    layer.effect: DropShadow {
                                        transparentBorder: true
                                        horizontalOffset: 0
                                        verticalOffset: 1
                                        color: "#e0e5ef"
                                        samples: 10
                                        radius: 10
                                    }
                                }

                                Rectangle {
                                    id: networkRectangle
                                    width: 200
                                    height: 150
                                    layer.enabled: true
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
                                    layer.effect: DropShadow {
                                        transparentBorder: true
                                        horizontalOffset: 0
                                        verticalOffset: 1
                                        color: "#e0e5ef"
                                        samples: 10
                                        radius: 10
                                    }
                                }

                                Rectangle {
                                    width: 250
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    layer.effect: DropShadow {
                                        color: "#e0e5ef"
                                        radius: 10
                                        transparentBorder: true
                                        samples: 10
                                        verticalOffset: 1
                                        horizontalOffset: 0
                                    }
                                    layer.enabled: true
                                    Label {
                                        id: levelTempLabel1
                                        color: "#888d91"
                                        text: qsTr("Акселерометр:")
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        anchors.leftMargin: 15
                                        anchors.rightMargin: 0
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
                                            layer.enabled: true
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
                                            layer.effect: DropShadow {
                                                transparentBorder: true
                                                horizontalOffset: 0
                                                verticalOffset: 1
                                                color: "#e0e5ef"
                                                samples: 10
                                                radius: 10
                                            }
                                        }
                                        Rectangle {
                                            id:batCurrentRectangle
                                            width: 150
                                            height: 150
                                            layer.enabled: true
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
                                            layer.effect: DropShadow {
                                                transparentBorder: true
                                                horizontalOffset: 0
                                                verticalOffset: 1
                                                color: "#e0e5ef"
                                                samples: 10
                                                radius: 10
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
                                    layer.enabled: true
                                    layer.effect: DropShadow {
                                        transparentBorder: true
                                        horizontalOffset: 0
                                        verticalOffset: 1
                                        color: "#e0e5ef"
                                        samples: 10
                                        radius: 10
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Item {
                x: 0
                y: 7
                clip: true
                ScrollView {
                    id:devMessageLogScroll
                    anchors.fill: parent
                    TextArea {
                        id: devMessageLog
                        placeholderText: "Сообщения"
                        anchors.fill: parent
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
                        font.pixelSize: platformStyle.fontSizeMedium
                        color: platformStyle.colorNormalLight
                    }
                }
            }

            Item {
                id:settingsItem
                clip: true
                Rectangle {
                    id: subBarup
                    height: 45
                    color: "#fdfdfb"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    TabBar {
                        id: tabSubProperty
                        height: 25
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        TabButtonUp {
                            name: "Акселерометр"
                            textLine: 1
                            widthBody: 130
                            useIcon: true
                            iconCode: "\\uF015  "
                        }

                        TabButtonUp {
                            name: "Сеть"
                            textLine: 1
                            widthBody: 120
                            useIcon: true
                            iconCode: "\\uF492  "
                        }
                        spacing: 5
                        currentIndex: stackSubProperty.currentIndex
                        anchors.top: parent.top
                        font.pointSize: 8
                        background: Rectangle {
                            color: "#00000000"
                        }
                        anchors.topMargin: 17
                    }
                }

                SwipeView {
                    id: stackSubProperty
                    currentIndex: tabSubProperty.currentIndex
                    anchors.left: subBarup.left
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    clip: true
                    anchors.top: subBarup.bottom
                    Item {
                        id: currentStackData
                        ScrollView {
                            Column {
                                spacing: 10
                                anchors.top: parent.top
                                Row {
                                    anchors.top: parent.top
                                    anchors.topMargin: 15
                                    width: 500
                                    height: 100
                                    Rectangle {
                                        id: accelCoefRect
                                        width: 500
                                        height: 250
                                        color: "#fdfdfb"
                                        anchors.left: parent.left
                                        layer.effect: DropShadow {
                                            color: "#e0e5ef"
                                            radius: 20
                                            transparentBorder: true
                                            samples: 10
                                            verticalOffset: 1
                                            horizontalOffset: 0
                                        }
                                        anchors.leftMargin: 15
                                        layer.enabled: true
                                        Label {
                                            text: "Коэффициенты:"
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                        }
                                        Column {
                                            id: column3
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 10
                                            anchors.top: parent.top
                                            anchors.topMargin: 30
                                            Row {
                                                spacing: 10
                                                Label {
                                                    text: "X:"
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                TextField {
                                                    id: accelCoefX
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                            Row {
                                                spacing: 10
                                                Label {
                                                    text: "Y:"
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                TextField {
                                                    id: accelCoefY
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                            Row {
                                                spacing: 10
                                                Label {
                                                    text: "Z:"
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                TextField {
                                                    id: accelCoefZ
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                            Row {
                                                spacing: 10
                                                Label {
                                                    text: "Угол отклонения:"
                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                TextField {
                                                    id: accelAngle
                                                    height: 30
                                                    width: 300
                                                    placeholderText: "введите значение"
                                                }
                                            }
                                        }
                                    }
                                    Column {
                                        anchors.top: parent.top
                                        anchors.topMargin: 0
                                        anchors.left: accelCoefRect.right
                                        anchors.leftMargin: 15
                                        spacing: 10
                                        Button {
                                            id: insertCurrentAccelValues
                                            width: 180
                                            height: 70
                                            text: "Использовать\nтекущие\nзначения"
                                            layer.effect: DropShadow {
                                                color: "#e0e5ef"
                                                radius: 20
                                                transparentBorder: true
                                                samples: 10
                                                verticalOffset: 1
                                                horizontalOffset: 0
                                            }
                                            anchors.leftMargin: 25
                                            layer.enabled: true
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
                                            layer.effect: DropShadow {
                                                color: "#e0e5ef"
                                                radius: 20
                                                transparentBorder: true
                                                samples: 10
                                                verticalOffset: 1
                                                horizontalOffset: 0
                                            }
                                            anchors.leftMargin: 25
                                            layer.enabled: true
                                            enabled: devIsConnected
                                            onClicked: {
                                                viewController.getCurrentDevCustomCommand("get current dev settings")
                                            }
                                        }
                                        Button {
                                            id: writeSettingsButton_1
                                            width: 180
                                            height: 50
                                            text: "Записать настройки"
                                            layer.effect: DropShadow {
                                                color: "#e0e5ef"
                                                radius: 20
                                                transparentBorder: true
                                                samples: 10
                                                verticalOffset: 1
                                                horizontalOffset: 0
                                            }
                                            anchors.leftMargin: 25
                                            layer.enabled: true
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
                                                viewController.setCurrentDevCustomCommandWithoutAckDialog("set current dev settings accel config", keys, values)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Item {
                        id: settingsStackData
                        ScrollView {
                            Column {
                                spacing: 10
                                anchors.top: parent.top
                                Row {
                                    anchors.top: parent.top
                                    anchors.topMargin: 15
                                    width: 500
                                    height: 100
                                    Rectangle {
                                        id: networlSettingsCoefRect
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        anchors.left: parent.left
                                        layer.effect: DropShadow {
                                            color: "#e0e5ef"
                                            radius: 20
                                            transparentBorder: true
                                            samples: 10
                                            verticalOffset: 1
                                            horizontalOffset: 0
                                        }
                                        anchors.leftMargin: 15
                                        layer.enabled: true
                                        Label {
                                            text: "Пароль:"
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                        }
                                        Column {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 0
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 10
                                            anchors.top: parent.top
                                            anchors.topMargin: 30
                                            TextField {
                                                id: networkPassword
                                                height: 30
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                width: 300
                                                placeholderText: "введите значение"
                                            }
                                        }
                                    }
                                    Button {
                                        id: readSetingsButton_2
                                        width: 180
                                        height: 50
                                        text: "Считать настройки"
                                        anchors.top: parent.top
                                        anchors.topMargin: 0
                                        anchors.left: networlSettingsCoefRect.right
                                        layer.effect: DropShadow {
                                            color: "#e0e5ef"
                                            radius: 20
                                            transparentBorder: true
                                            samples: 10
                                            verticalOffset: 1
                                            horizontalOffset: 0
                                        }
                                        anchors.leftMargin: 25
                                        layer.enabled: true
                                        enabled: devIsConnected
                                        onClicked: {
                                            viewController.getCurrentDevCustomCommand("get current dev settings")
                                        }
                                    }

                                    Button {
                                        id: writeSettingsButton_2
                                        width: 180
                                        height: 50
                                        text: "Записать настройки"
                                        anchors.top: parent.top
                                        anchors.topMargin: 60
                                        anchors.left: networlSettingsCoefRect.right
                                        layer.effect: DropShadow {
                                            color: "#e0e5ef"
                                            radius: 20
                                            transparentBorder: true
                                            samples: 10
                                            verticalOffset: 1
                                            horizontalOffset: 0
                                        }
                                        anchors.leftMargin: 25
                                        layer.enabled: true
                                        onClicked: {
                                            writeNetworkConfig()
                                        }
                                    }
                                }
                            }
                            anchors.fill: parent
                            clip: true
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
        standardButtons: StandardButton.Apply
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
        onApply: {
            close()
        }
    }

    Rectangle {
        id: busyIndicator
        width: 350
        height: 200
        radius: 20
        visible: false
        property string message: "Ожидание ответа..."
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        BusyIndicator {
            id: waitReadyIndicator
            width: 96
            height: 96
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
        Label {
            text: busyIndicator.message
            anchors.top: waitReadyIndicator.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            horizontalOffset: 0
            verticalOffset: 1
            color: "#e0e5ef"
            samples: 10
            radius: 10
        }
    }
}
