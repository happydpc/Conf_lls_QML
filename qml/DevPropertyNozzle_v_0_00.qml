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

    function setNoReady() {
        devProperty.isReady = false
        setWriteSettingsIsNoAvailable()
    }
    function setReady() {
        devProperty.isReady = true
    }
    function setResetState() {
        tabProperty.setCurrentIndex(0)
        stackSubProperty.setCurrentIndex(0)
        setNoReady()
        setWriteSettingsIsAvailable()
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
            if(keys[i].toLowerCase() === "devtypename"){
                typeDeviceText.text = values[i]
            }
            if(keys[i].toLowerCase() === "serialnum"){
                snText.text = values[i]
            }
            if(keys[i].toLowerCase() === "firmware"){
                versionFirmwareText.text = values[i]
            }
        }
    }

    function setCustomCommandExecuted(keys, args, ackMessageIsVisible) {
        var i = 0;
        switch(keys[0].toLowerCase()) {
        case "getacceldata" :
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "accelx"){
                    accelXProgressBar.value = parseFloat(args[i])
                }
                if(keys[i].toLowerCase() === "accely"){
                    accelYProgressBar.value = parseFloat(args[i])
                }
                if(keys[i].toLowerCase() === "accelz"){
                    accelZProgressBar.value = parseFloat(args[i])
                }
            }
            break;
        case "getnetworkdata":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "networkparentip"){
                    networkParentIp.text = args[i]
                }
            }
            break;
            // it last command to read the settings
        case "getnetworkconfig":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "networkpassword"){
                    networkPassword.text = args[i]
                }
            }
            break;
        case "getaccelconfig":
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
                if(keys[i].toLowerCase() === "accelconfdelta") {
                    accelCoeDeltaX.text = args[i]
                }
            }
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно считаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break;
        case "getcardproperty":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "cardnumber"){
                    cardNumber.text = args[i].toUpperCase()
                }
            }
            break;
        case "getbatteryproperty":
            for(i=0; i<keys.length; i++) {
                if(keys[i].toLowerCase() === "powervoltage"){
                    batteryVoltage.value = parseFloat(args[i])
                }
                if(keys[i].toLowerCase() === "powercurrentresouresavailable"){
                    batteryResourseAvailable.value = parseFloat(args[i])
                }
            }
            break;
        case "setnetworkpassword":
        case "setaccelconfig":
        case "setaccelusecurrentvaluesasnullpoint":
        case "setnetworkconfig":
            if(ackMessageIsVisible) {
                dialogInfoMessage.message = "Настройки успешно записаны"
                dialogInfoMessage.title = "Настройки"
                dialogInfoMessage.open()
            }
            break
        default: break;
        }
    }

    function setUpdatePeriodicValues() {
        devProperty.isReady = true
        var list = viewController.getCurrentDevChart()
        currentChartLines.clear();
        chartCurrentValue.graphLength = list.length
        chartCurrentValue.graphAmplitudeMax = 0

        for(var i=0; i<list.length; i++) {
            if(chartCurrentValue.graphAmplitudeMax < list[i]) {
                chartCurrentValue.graphAmplitudeMax = list[i];
            }
        }
        for(i=0; i<list.length; i++) {
            currentChartLines.append(i, list[i]);
        }
    }

    function addLogMessage(codeMessage, message) {
        log.append(message)
    }

    function addDeviceLogMessage(message) {
        if(devMessageLog.length > 512) {
            devMessageLog.remove(0, message.length + 100)
        }
        devMessageLog.append(message)
    }

    function writeAccelConfig() {
        var keys = [];
        var values = [];
        keys.push("accelConfX")
        values.push(accelCoefX.text)
        keys.push("accelConfY")
        values.push(accelCoefY.text)
        keys.push("accelConfZ")
        values.push(accelCoefZ.text)
        keys.push("accelConfDelta")
        values.push(accelCoeDeltaX.text)
        viewController.setCurrentDevCustomCommandWithoutAckDialog("set current dev settings accel config", keys, values)
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
        property bool isReady: true
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
                                    enabled: devProperty.isReady
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
                                    enabled: devProperty.isReady
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
                                    enabled: devProperty.isReady
                                    anchors.left: lversionFirmwareText.right
                                    anchors.right: parent.right
                                    anchors.leftMargin: 5
                                    readOnly: true
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
                                        suffixText: "V"
                                        textColor: "#888d91"
                                        enabled: devProperty.isReady
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
                                    width: 150
                                    height: 150
                                    layer.enabled: true
                                    radius: 15
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
                                        progressColor: "#05fff0"
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
                                        suffixText: "mA"
                                        textColor: "#888d91"
                                        enabled: devProperty.isReady
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
                                        y: 55
                                        text: qsTr("")
                                        anchors.right: parent.right
                                        anchors.rightMargin: 5
                                        anchors.left: parent.left
                                        anchors.leftMargin: 5
                                        placeholderText: "номер карты"
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
                                    Label {
                                        text: qsTr("Сеть")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }

                                    TextField {
                                        id: networkParentIp
                                        y: 55
                                        text: qsTr("")
                                        anchors.right: parent.right
                                        anchors.rightMargin: 5
                                        anchors.left: parent.left
                                        anchors.leftMargin: 5
                                        placeholderText: "ip адрес"
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
                                    width: 150
                                    height: 150
                                    radius: 15
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

                                    Row {
                                        spacing: 10
                                        x: 5
                                        y: 41
                                        Label {
                                            text: "X:"
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        ProgressBar {
                                            id: accelXProgressBar
                                            to: 100
                                            width: 100
                                            value: 0
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }

                                    Row {
                                        spacing: 10
                                        x: 5
                                        y: 72
                                        Label {
                                            text: "Y:"
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        ProgressBar {
                                            id: accelYProgressBar
                                            to: 100
                                            width: 100
                                            value: 0
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }

                                    Row {
                                        spacing: 10
                                        x: 5
                                        y: 104
                                        Label {
                                            text: "Z:"
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        ProgressBar {
                                            id: accelZProgressBar
                                            to: 100
                                            width: 100
                                            anchors.verticalCenter: parent.verticalCenter
                                            value: 0
                                        }
                                    }
                                }
                            }
                        }
                        Column {
                            id: column1
                            width: 470
                            height: 250
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            Rectangle {
                                id: rectangle
                                height: 250
                                // - 50
                                color: "#ffffff"
                                radius: 0
                                anchors.fill: parent
                                ChartView {
                                    id: chartCurrentValue
                                    theme: ChartView.ChartThemeLight
                                    title: "RSSI"
                                    antialiasing: true
                                    property int graphLength: 1
                                    property int graphAmplitudeMax: 1
                                    height: 250
                                    anchors.fill: parent
                                    ValueAxis {
                                        id: currentChartAxisX
                                        min: 0
                                        max: chartCurrentValue.graphLength
                                        tickCount: 5
                                    }
                                    ValueAxis {
                                        id: currentChartAxisY
                                        min: -0.1
                                        max: chartCurrentValue.graphAmplitudeMax
                                        tickCount: 5
                                    }
                                    LineSeries {
                                        id: currentChartLines
                                        axisX: currentChartAxisX
                                        axisY: currentChartAxisY
                                    }
                                    enabled: devProperty.isReady
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

            Item {
                x: 0
                y: 7
                clip: true
                ScrollView {
                    anchors.fill: parent
                    TextArea {
                        id: devMessageLog
                        text: qsTr("")
                        placeholderText: "Сообщения"
                        anchors.rightMargin: 10
                        anchors.leftMargin: 10
                        anchors.bottomMargin: 10
                        anchors.topMargin: 10
                        anchors.fill: parent
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
                    onCurrentIndexChanged: {
                        //                        if(stackSubProperty.currentItem == settingsStackData) {
                        //                            viewController.getCurrentDevCustomCommand("get current dev settings witout dialog")
                        //                        }
                    }

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
                                        height: 160
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
                                        }
                                    }
                                    Rectangle {
                                        id: accelDeltaRect
                                        width: 500
                                        height: 90
                                        color: "#fdfdfb"
                                        anchors.top: accelCoefRect.bottom
                                        anchors.topMargin: 15
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
                                            text: "Дельта:"
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                        }
                                        TextField {
                                            id: accelCoeDeltaX
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            anchors.top: parent.top
                                            anchors.topMargin: 30
                                            height: 30
                                            width: 300
                                            placeholderText: "введите значение"
                                        }
                                    }

                                    Button {
                                        id: readSetingsButton_1
                                        width: 180
                                        height: 50
                                        text: "Считать настройки"
                                        anchors.top: parent.top
                                        anchors.topMargin: 0
                                        anchors.left: accelCoefRect.right
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
                                        enabled: devProperty.isReady
                                        onClicked: {
                                            viewController.getCurrentDevCustomCommand("get current dev settings")
                                        }
                                    }

                                    Button {
                                        id: writeSettingsButton_1
                                        width: 180
                                        height: 50
                                        text: "Записать настройки"
                                        anchors.top: parent.top
                                        anchors.topMargin: 60
                                        anchors.left: accelCoefRect.right
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
                                        enabled: devProperty.isReady
                                        onClicked: {
                                            writeAccelConfig()
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
                                        enabled: devProperty.isReady
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
                                        enabled: devProperty.isReady
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
