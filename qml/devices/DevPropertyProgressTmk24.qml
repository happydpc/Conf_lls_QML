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

    property bool isNoiseDetected: false
    property bool devIsConnected: false
    property bool devIsReady: false
    property string  id: ""

    property var tarArrayDinamicCreateItem: []

    function setInitProperty(devKeyProperty, devValueProperty) {
        for(var i=0; i<devKeyProperty.length; i++) {
            if(devKeyProperty[i] === "id") {
                id = devValueProperty[i]
            }
        }
    }

    function removeAll() {
        for(var index = tarTabViewMultiple.columnCount-1; index>=0; index--) {
            var delRow = tarTabViewMultiple.getColumn(index)
            tarTabViewMultiple.removeColumn(index)
            delRow.destroy()
            delete delRow
        }
        while(tarArrayDinamicCreateItem.length !== 0) {
            var column = tarArrayDinamicCreateItem[0]
            column.destroy()
            delete column
            tarArrayDinamicCreateItem.shift()
        }
        tarTabViewMultiple.model.clear()
    }

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

    function devShowMessage(messageHeader, message) {
        messageDialog.headerTitile = messageHeader
        messageDialog.message = message
        messageDialog.open()
    }

    function setWriteSettingsIsAvailable() {
        writeSettingsButton_1.enabled = true
        writeSettingsButton_2.enabled = true
        writeSettingsButton_3.enabled = true
        writeSettingsButton_4.enabled = true
        writeSettingsButton_5.enabled = true
    }

    function setWriteSettingsIsNoAvailable() {
        writeSettingsButton_1.enabled = false
        writeSettingsButton_2.enabled = false
        writeSettingsButton_3.enabled = false
        writeSettingsButton_4.enabled = false
        writeSettingsButton_5.enabled = false
    }

    function getId() {
        return id;
    }

    function insertPeriodicData(keys, values) {
        devIsReady = true
        devIsConnected = true
        parseInputData(keys, values)
    }

    function setCustomCommandExecuted(keys, args, ackMessageIsVisible) {
        var i = 0;
        switch(keys[0]) {
        case "lls_read_settings":
            parseInputData(keys, args)
            if(ackMessageIsVisible) {
                messageDialog.title = "Чтение настроек"
                messageDialog.message = "Настройки успешно считаны"
                messageDialog.open()
            }
            break;
        case "lls_write_settings":
            if(ackMessageIsVisible) {
                messageDialog.title = "Запись настроек"
                messageDialog.message = "Настройки успешно записаны"
                messageDialog.open()
            }
            break;
        case "lls_read_errors":
            if(ackMessageIsVisible) {
                messageDialog.title = "Чтение ошибок"
                messageDialog.message = "Ошибки успешно считаны"
                messageDialog.open()
            }
            parseInputData(keys, args)
            break;

        case "lls_read_lvl_all":
            parseInputData(keys, args)
            break;
        case "lls_calibrate_max":
            if(ackMessageIsVisible) {
                messageDialog.title = "Калибровка"
                messageDialog.message = "Калибровка верхнего уровня\nуспешно успешно произведена"
                messageDialog.open()
            }
            break;
        case "lls_calibrate_min":
            if(ackMessageIsVisible) {
                messageDialog.title = "Калибровка"
                messageDialog.message = "Калибровка нижнего уровня\nуспешно успешно произведена"
                messageDialog.open()
            }
            break;
        case "lls_read_cal_table":
            if(ackMessageIsVisible) {
                messageDialog.title = "Тарировочная таблица"
                messageDialog.message = "Тарировочная таблица успешно считана"
                messageDialog.open()
            }
            remakeTarTable()
            readTarTable()
            break;
        case "lls_write_cal_table":
            if(ackMessageIsVisible) {
                messageDialog.title = "Тарировочная таблица"
                messageDialog.message = "Тарировочная таблица успешно записана"
                messageDialog.open()
            }
            break;
        case "lls_read_lvl_all": break;
        default: break;
        }
    }

    function parseInputData(keys, values) {
        for(var i=0; i<keys.length; i++) {
            if(keys[i] === "k1_value") {
                k1.text = values[i]
            } else if(keys[i] === "k2_value") {
                k2.text = values[i]
            } else if(keys[i] === "typeTempCompensation_value") {
                typeTempCompensation.currentIndex = values[i]
            } else if(keys[i] === "periodicSendType_value") {
                periodicSendType.currentIndex = values[i]
            } else if(keys[i] === "periodicSendTime_value") {
                periodicSendTime.value = values[i]
            } else if(keys[i] === "typeOutMessage_value") {
                typeOutMessage.currentIndex = values[i]
            } else if(keys[i] === "typeInterpolation_value") {
                typeInterpolation.currentIndex = values[i]
            } else if(keys[i] === "typeFiltration_value") {
                typeFiltration.currentIndex = values[i]
            } else if(keys[i] === "filterLenghtMediana_value") {
                filterLenghtMediana.value = values[i]
            } else if(keys[i] === "filterAvarageValueSec_value") {
                filterAvarageValueSec.value = values[i]
            } else if(keys[i] === "filterValueR_value") {
                filterValueR.value= values[i]
            } else if(keys[i] === "filterValueQ_value") {
                filterValueQ.value = values[i]
            } else if(keys[i] === "minLevelValue_value") {
                minLevelValue.value = values[i]
            } else if(keys[i] === "maxLevelValue_value") {
                maxLevelValue.value = values[i]
            } else if(keys[i] === "masterSlaveModes_value") {
                masterSlaveModes.currentIndex = values[i]
            } else if(keys[i] === "baudrateRs232Values_value") {
                baudrateRs232Values.currentIndex = values[i]
            } else if(keys[i] === "baudrateRs485Values_value") {
                baudrateRs485Values.currentIndex = values[i]
            } else if(keys[i] === "masterSlaveFullCountes_value") {
                masterSlaveFullCountes.value = values[i]
            } else if(keys[i] === "masterSlaveSlaveId_1_value") {
                masterSlaveSlaveId_1.value = values[i]
            } else if(keys[i] === "masterSlaveSlaveId_2_value") {
                masterSlaveSlaveId_2.value = values[i]
            } else if(keys[i] === "masterSlaveSlaveId_3_value") {
                masterSlaveSlaveId_3.value = values[i]
            } else if(keys[i] === "masterSlaveSlaveId_4_value") {
                masterSlaveSlaveId_4.value = values[i]
            } else if(keys[i] === "devTypeName"){
                typeDeviceText.text = values[i]
            } else if(keys[i] === "serialNum"){
                snText.text = values[i]
            } else if(keys[i] === "versionFirmare"){
                versionFirmwareText.text = values[i]
            } else if(keys[i] === "fuelProcent") {
                if(values[i] > 100) {
                    values[i] = 0
                }
                fuelLevelProgress.value = values[i]
            } else if(keys[i] === "fuelProcent") {
            } else if(keys[i] === "cnt") {
                levelCnt.value = values[i]
            } else if(keys[i] === "freq") {
                levelFreq.value = values[i]
            } else if(keys[i] === "temp") {
                levelTemp.value = values[i]
            } else if(keys[i] === "noiseDetected") {
                if((chartTarCurrentValuesMultiple.animateColorUp.running == false
                    & (chartTarCurrentValuesMultiple.animateColorDown.running == false))) {
                    if(values[i] == true) {
                        chartTarCurrentValuesMultiple.animateColorUp.start()
                    }
                }
            } else if(keys[i] === "ReplayNotComeRs485") {
                typeInterpolation.currentIndex = values[i]
            } else if(keys[i] === "Rs232Error") {
                typeFiltration.currentIndex = values[i]
            } else if(keys[i] === "Rs485Error") {
                filterLenghtMediana.value = values[i]
            } else if(keys[i] === "Slave1Error") {
                error5Label.error5 = values[i]
            } else if(keys[i] === "Slave2Error") {
                error6Label.error6 = values[i]
            } else if(keys[i] === "Slave3Error") {
                error7Label.error7 = values[i]
            } else if(keys[i] === "Slave4Error") {
                error8Label.error8 = values[i]
            } else if(keys[i] === "chartValue") {
                if(chartCurrentValue.dataList.length > 50) {
                    chartCurrentValue.dataList.shift()
                }
                chartCurrentValue.dataList.push(parseInt(values[i]))
                chartCurrentValueLines.clear();
                chartCurrentValue.graphLength = chartCurrentValue.dataList.length - 1
                chartCurrentValue.graphAmplitudeMax = 0
                for(var chartIter=0; chartIter<chartCurrentValue.dataList.length; chartIter++) {
                    if(chartCurrentValue.dataList[chartIter] > chartCurrentValue.graphAmplitudeMax) {
                        chartCurrentValue.graphAmplitudeMax = chartCurrentValue.dataList[chartIter];
                    }
                    if(chartCurrentValue.dataList[chartIter] < chartCurrentValue.graphAmplitudeMin) {
                        chartCurrentValue.graphAmplitudeMin = chartCurrentValue.dataList[chartIter];
                    }
                }
                for(chartIter=0; chartIter<chartCurrentValue.dataList.length; chartIter++) {
                    chartCurrentValueLines.append(chartIter, chartCurrentValue.dataList[chartIter]);
                }
            } else if(keys[i] === "GenFreq0") {
                error4Label.error4 = values[i]
            } else if(keys[i] === "MaxFreqOut") {
                error2Label.error2 = values[i]
            } else if(keys[i] === "MinFreqOut") {
                error3Label.error3 = values[i]
            } else if(keys[i] === "NotCalibrated") {
                error1Label.error1 = values[i]
            } else if(keys[i] === "QeueManagerError") {
                periodicSendTime.value = values[i]
            } else if(keys[i] === "ReplayNotComeRs232") {
                typeOutMessage.currentIndex = values[i]
            } else if(keys[i] === "ReplayNotComeRs485") {
                typeInterpolation.currentIndex = values[i]
            } else if(keys[i] === "Rs232Error") {
                typeFiltration.currentIndex = values[i]
            } else if(keys[i] === "Rs485Error") {
                filterLenghtMediana.value = values[i]
            } else if(keys[i] === "Slave1Error") {
                error5Label.error5 = values[i]
            } else if(keys[i] === "Slave2Error") {
                error6Label.error6 = values[i]
            } else if(keys[i] === "Slave3Error") {
                error7Label.error7 = values[i]
            } else if(keys[i] === "Slave4Error") {
                error8Label.error8 = values[i]
            }
        }
    }

    Timer {
        id: timerUpdateRepeat
        interval: 1500
        running: true
        repeat: true
        onTriggered: {
            if(devIsConnected) {
                updateCurrentTarTableChart()
            }
        }
    }

    function updateCurrentTarTableChart() {
        var devCount = viewController.getStayedDevTarrirCount()
        var devId = viewController.getStayedDevTarrir_DevProperty("id")
        var colorArray = []
        colorArray.push("#f34b4b")
        colorArray.push("#4bd5f3")
        colorArray.push("#f34be1")
        colorArray.push("#4bf3c6")
        colorArray.push("#4b4bf3")
        colorArray.push("#be4bf3")
        colorArray.push("#0d8741")
        colorArray.push("#4bf3c6")
        colorArray.push("#4b4bf3")
        colorArray.push("#be4bf3")
        colorArray.push("#0d8741")
        chartTarCurrentValuesMultiple.removeAllSeries();
        var chartArray = undefined
        var maxGraphAmplitude = 0

        for(var devIter=0; devIter<devCount; devIter++) {
            var res = viewController.getTarCurrentDeviceData(devIter)
            if(res !== undefined) {
                var dataArray = tarListDevice.model.get(devIter)
                if(dataArray !== undefined) {
                    dataArray["valueCnt"] = res[0]
                    dataArray["valueFuelLevel"] = res[2]
                    tarListDevice.model.set(devIter, dataArray)
                }
            }
            //-- chart
            chartArray = viewController.getTarCurrentDeviceChartData(devIter)
            if(chartArray !== undefined) {
                var maxGraphLen = chartArray.length
                for(var chartIter=0; chartIter<chartArray.length; chartIter++) {
                    if(maxGraphAmplitude < chartArray[chartIter]) {
                        maxGraphAmplitude = chartArray[chartIter];
                    }
                }
                var tAxisXMultipleMin = 0;
                var tAxisXMultipleMax = chartArray.length
                var tAxisYMultipleMin = 0;
                var tAxisYMultipleMax = maxGraphAmplitude

                var line = chartTarCurrentValuesMultiple.createSeries(ChartView.SeriesTypeLine,
                                                                      "ID" + devId[devIter], currentTarChartAxisXMultiple, currentTarChartAxisYMultiple);
                line.color = colorArray[devIter]

                for(chartIter=0; chartIter<chartArray.length; chartIter++) {
                    var tvalue = parseInt(chartArray[chartIter])
                    line.append(chartIter, tvalue);
                }
            }
        }
        if(chartArray !== undefined) {
            chartTarCurrentValuesMultiple.graphLength = chartArray.length
            chartTarCurrentValuesMultiple.graphAmplitudeMax = maxGraphAmplitude
            chartTarCurrentValuesMultiple.graphAmplitudeMaxChanged();
        }
    }

    function addLogMessage(codeMessage, message) {
        if(logListView.model.length > 50) {
            logListView.model.shift()
        }
        logListView.model.append({"message":message,"status":codeMessage})
    }

    function writeSettings() {
        var settings = [];
        var key = [];
        key.push("k1_value")
        settings.push(k1.text)
        key.push("k2_value")
        settings.push(k2.text)
        key.push("typeTempCompensation_value")
        settings.push(typeTempCompensation.currentIndex)
        key.push("periodicSendType_value")
        settings.push(periodicSendType.currentIndex)
        key.push("periodicSendTime_value")
        settings.push(periodicSendTime.value)
        key.push("typeOutMessage_value")
        settings.push(typeOutMessage.currentIndex)
        key.push("typeInterpolation_value")
        settings.push(typeInterpolation.currentIndex)
        key.push("typeFiltration_value")
        settings.push(typeFiltration.currentIndex)
        key.push("filterLenghtMediana_value")
        settings.push(filterLenghtMediana.value)
        key.push("filterAvarageValueSec_value")
        settings.push(filterAvarageValueSec.value)
        key.push("filterValueR_value")
        settings.push(filterValueR.value)
        key.push("filterValueQ_value")
        settings.push(filterValueQ.value)
        key.push("minLevelValue_value")
        settings.push(minLevelValue.value)
        key.push("maxLevelValue_value")
        settings.push(maxLevelValue.value)
        key.push("masterSlaveModes_value")
        settings.push(masterSlaveModes.currentIndex)
        key.push("baudrateRs232Values_value")
        settings.push(baudrateRs232Values.currentIndex)
        key.push("baudrateRs485Values_value")
        settings.push(baudrateRs485Values.currentIndex)
        key.push("masterSlaveFullCountes_value")
        settings.push(masterSlaveFullCountes.value)
        key.push("masterSlaveSlaveId_1_value")
        settings.push(masterSlaveSlaveId_1.value)
        key.push("masterSlaveSlaveId_2_value")
        settings.push(masterSlaveSlaveId_2.value)
        key.push("masterSlaveSlaveId_3_value")
        settings.push(masterSlaveSlaveId_3.value)
        key.push("masterSlaveSlaveId_4_value")
        settings.push(masterSlaveSlaveId_4.value)
        viewController.setCurrentDevCustomCommand("set current dev settings", key, settings)
    }

    function remakeTarTableChart() {
        chartTarTableMultiple.removeAllSeries();
        var colorArray = []
        colorArray.push("#f34b4b")
        colorArray.push("#4bd5f3")
        colorArray.push("#f34be1")
        colorArray.push("#4bf3c6")
        colorArray.push("#4b4bf3")
        colorArray.push("#be4bf3")
        colorArray.push("#0d8741")

        var tarSize = viewController.getStayedDevTarrirCount()
        for(var deviceCounter=0; deviceCounter<tarSize; deviceCounter++) {
            var roleLiters = "roleLiters" + deviceCounter
            var roleFuelLevel = "roleFuelLevel" + deviceCounter
            var devId = viewController.getStayedDevTarrir_DevProperty("id")

            var maxvalueFuelLevel = 0;
            var maxValueLitrs = 0;
            var tarArrayLitrs = [];
            var tarArrayFuelLevel = [];

            for(var itemCounter=0; itemCounter<tarTabViewMultiple.rowCount; itemCounter++) {
                var item = tarTabViewMultiple.model.get(itemCounter)
                if(item !== undefined) {
                    tarArrayLitrs.push(item[roleLiters])
                    tarArrayFuelLevel.push(item[roleFuelLevel])
                    if(maxvalueFuelLevel < parseInt(item[roleFuelLevel])) {
                        maxvalueFuelLevel = parseInt(item[roleFuelLevel])
                    }
                    if(maxValueLitrs < parseInt(item[roleLiters])) {
                        maxValueLitrs = parseInt(item[roleLiters])
                    }
                    console.log(roleLiters + " " + item[roleFuelLevel] + "\nValue Litrs=" + item[roleLiters])
                } else {
                    tarArrayLitrs.push("0")
                    tarArrayFuelLevel.push("0")
                }
            }

            var line = chartTarTableMultiple.createSeries(ChartView.SeriesTypeLine, "ID" + devId[deviceCounter], chartTarTableAxisXMultiple, chartTarTableAxisYMultiple);
            line.color = colorArray[deviceCounter]
            chartTarTableAxisXMultiple.min = 0;
            chartTarTableAxisXMultiple.max = maxValueLitrs
            chartTarTableAxisYMultiple.min = 0;
            chartTarTableAxisYMultiple.max = parseInt(maxvalueFuelLevel)

            chartTarTableMultiple.chartTarTableAmplitudeMax = parseInt(maxvalueFuelLevel)
            chartTarTableMultiple.chartTarTableLength = maxValueLitrs

            console.log("MaxLevel =" + chartTarTableMultiple.chartTarTableAmplitudeMax)
            for(var i=0; i<tarArrayFuelLevel.length; i++) {
                line.append(parseInt(tarArrayLitrs[i]), parseInt(tarArrayFuelLevel[i]));
                console.log("Add=" + i + " " + tarArrayLitrs[i])
            }
        }
    }

    function addTarStepValue(rowIndex) {
        if(rowIndex === -1) {
            rowIndex = 0
        } else {
            rowIndex++
        }
        // если таблица пустая
        // создаем строку и заносим в нее текущие значения по устройствам
        // пока не переберем все уст-ва
        var itemValue = {}
        var devCount = viewController.getStayedDevTarrirCount()
        var devId = viewController.getStayedDevTarrir_DevProperty("id")

        for(var devIndex=0; devIndex<devCount; devIndex++) {
            var valueFuelLevel = 0
            var valueLiters = 0
            var value = viewController.getTarCurrentDeviceData(devIndex)
            var roleLiters = "roleLiters" + devIndex
            var roleFuelLevel = "roleFuelLevel" + devIndex

            valueFuelLevel = value[0]
            if(valueFuelLevel == undefined) {
                valueFuelLevel = "0"
            }
            // попытка взять предыдущее значение литров
            // если есть
            var lastLiter = tarTabViewMultiple.model.get(rowIndex-1)
            if(lastLiter !== undefined) {
                valueLiters = lastLiter[roleLiters]
                if(valueLiters == undefined) {
                    valueLiters = "0"
                }
                if(valueLiters.length === 0) {
                    valueLiters = "0"
                }
            } else {
                valueLiters = value[1]
                if(valueLiters == undefined) {
                    valueLiters = "0"
                }
                if(valueLiters.length === 0) {
                    valueLiters = "0"
                }
            }
            itemValue[roleLiters] = valueLiters;
            itemValue[roleFuelLevel] = valueFuelLevel;
        }
        if(tarTabViewMultiple.model.get(rowIndex) === undefined) {
            tarTabViewMultiple.model.append(itemValue)
        } else {
            tarTabViewMultiple.model.insert(rowIndex, itemValue)
        }
        tarTabViewMultiple.currentRow = tarTabViewMultiple.currentRow+1
        timerAffterRefrashTarTable.start()
    }

    function removeTarStepValue(index) {
        // если ничего не выбрано выходим
        if(index !== -1) { // удаляем
            tarTabViewMultiple.model.remove(index)
            timerAffterRefrashTarTable.start()
        }
    }

    function remakeTarTable() {
        tarListDevice.model.clear()
        removeAll()
        var tarSize = viewController.getStayedDevTarrirCount()
        var devType = []
        var devId = []
        var devSn = []
        devType = viewController.getStayedDevTarrir_DevProperty("type")
        devId =  viewController.getStayedDevTarrir_DevProperty("id")
        devSn = viewController.getStayedDevTarrir_DevProperty("sn")
        for(var i=0; i<tarSize; i++) { // добавляем на list with current data
            tarListDevice.model.append({"devTyp":devType[i],"devId":devId[i],"devSn":devSn[i],"valueCnt":"0","valueFuelLevel":"0"})
        }
        // добавляем в таблицу как столблец для девайса
        for(var i2=0; i2<tarSize; i2++) {
            var component = Qt.createComponent("DevPropertyProgressTmk24TarTableDelegate.qml");
            var tableViewColumn = component.createObject(tarTabViewMultiple);
            tableViewColumn.title = qsTr("Объем[ID-%1]").arg(devId[i2])
            tableViewColumn.role = "roleLiters" + i2
            tableViewColumn.width = 100
            tarArrayDinamicCreateItem.push(tableViewColumn)
            tarTabViewMultiple.addColumn(tableViewColumn)
            console.log("addeted1 =" + tableViewColumn.role)
            tableViewColumn.valueIsChanged.connect(function(role, text, modelChanged) {
                var curRow = tarTabViewMultiple.currentRow
                modelChanged[role] = text
                tarTabViewMultiple.model.set(curRow, modelChanged)
                remakeTarTableChart()
            });
            component = Qt.createComponent("DevPropertyProgressTmk24TarTableDelegate.qml");
            tableViewColumn = component.createObject(tarTabViewMultiple);
            tableViewColumn.title = qsTr("Ур.топ-ва[ID-%1]").arg(devId[i2])
            tableViewColumn.role = "roleFuelLevel" + i2
            tableViewColumn.width = 100
            tarArrayDinamicCreateItem.push(tableViewColumn)
            tarTabViewMultiple.addColumn(tableViewColumn)
            tableViewColumn.valueIsChanged.connect(function(role, text, modelChanged) {
                var curRow = tarTabViewMultiple.currentRow
                modelChanged[role] = text
                tarTabViewMultiple.model.set(curRow, modelChanged)
                remakeTarTableChart()
            });
        }
        var newModel = Object()
        for(var i=0; i<32; i++) {
        newModel["roleLiters"+i] = "NA"
        newModel["roleFuelLevel"+i]= "NA"
        }
        tarTabViewMultiple.model.set(0, newModel);
    }

    function writeTarTable() {
        var devCount = viewController.getStayedDevTarrirCount()
        var devType = []
        var devId = []
        var devSn = []
        devType = viewController.getStayedDevTarrir_DevProperty("type")
        devId =  viewController.getStayedDevTarrir_DevProperty("id")
        devSn = viewController.getStayedDevTarrir_DevProperty("sn")

        // считываем данные по ролям
        for(var count=0; count<devCount; count++) {
            var valueFuelLevel = 0
            var valueLiters = 0
            var roleLiters = "roleLiters" + count
            var roleFuelLevel = "roleFuelLevel" + count
            var jsonArrayCnt = []
            var jsonArrayLiters = []
            // считываем все шаги для одного устройства
            var modelTarSize = tarTabViewMultiple.model.count
            for(var subCount=0; subCount<modelTarSize; subCount++) {
                var values = tarTabViewMultiple.model.get(subCount)
                if(values !== undefined) {
                    valueLiters = values[roleLiters]
                    valueFuelLevel = values[roleFuelLevel]
                    if(valueLiters == undefined) {
                        valueLiters = "0"
                    }
                    if(valueFuelLevel == undefined) {
                        valueFuelLevel = "0"
                    }
                } else {
                    valueLiters = values[1]
                    if(valueLiters == undefined) {
                        valueLiters = "0"
                    }
                    valueFuelLevel = values[0]
                    if(valueFuelLevel == undefined) {
                        valueFuelLevel = "0"
                    }
                }
                jsonArrayCnt.push(valueFuelLevel)
                jsonArrayLiters.push(valueLiters)
            }
            viewController.setTableFromFrontEnd(devId[count], jsonArrayLiters, jsonArrayCnt)
        }
        viewController.sendReqWriteTarrirAllDev()
    }

    function saveTarTableToCsv(pathFile) {
        var devCount = viewController.getStayedDevTarrirCount()
        var devType = []
        var devId = []
        var devSn = []
        devType = viewController.getStayedDevTarrir_DevProperty("type")
        devId =  viewController.getStayedDevTarrir_DevProperty("id")
        devSn = viewController.getStayedDevTarrir_DevProperty("sn")

        // считываем данные по ролям
        for(var count=0; count<devCount; count++) {
            var valueFuelLevel = 0
            var valueLiters = 0
            var roleLiters = "roleLiters" + count
            var roleFuelLevel = "roleFuelLevel" + count
            var jsonArrayCnt = []
            var jsonArrayLiters = []
            // считываем все шаги для одного устройства
            var modelTarSize = tarTabViewMultiple.model.count
            for(var subCount=0; subCount<modelTarSize; subCount++) {
                var values = tarTabViewMultiple.model.get(subCount)
                if(values !== undefined) {
                    valueLiters = values[roleLiters]
                    valueFuelLevel = values[roleFuelLevel]
                    if(valueLiters == undefined) {
                        valueLiters = "0"
                    }
                    if(valueFuelLevel == undefined) {
                        valueFuelLevel = "0"
                    }
                } else {
                    valueLiters = values[1]
                    if(valueLiters == undefined) {
                        valueLiters = "0"
                    }
                    valueFuelLevel = values[0]
                    if(valueFuelLevel == undefined) {
                        valueFuelLevel = "0"
                    }
                }
                jsonArrayCnt.push(valueFuelLevel)
                jsonArrayLiters.push(valueLiters)
            }
            viewController.setTableFromFrontEnd(devId[count], jsonArrayLiters, jsonArrayCnt)
        }
        viewController.sendReqExportTarrirAllDevToCsv(pathFile)
    }

    function readTarTable() {
        var devCount = viewController.getStayedDevTarrirCount()
        var jsonArray = []
        // пока не переберем все уст-ва
        for(var devIndex=0; devIndex<devCount; devIndex++) {
            var table = viewController.getTableAtDevice(devIndex)
            var parity = 0
            var paramCounter = 0;
            var valueFuelLevel = "0"
            var valueLiters = "0"
            var stepCount = viewController.getTarMaxCountStep() *2 // it pair
            for(var devTableRow=0; devTableRow<stepCount; devTableRow++) {
                if(parity == 0) {
                    parity = 1;
                    valueLiters = table[devTableRow]
                    if(valueLiters == undefined) {
                        valueLiters = ""
                    }
                } else {
                    parity = 0;
                    valueFuelLevel = table[devTableRow]
                    if(valueFuelLevel == undefined) {
                        valueFuelLevel = ""
                    }

                    var roleLiters = "roleLiters" + devIndex
                    var roleFuelLevel = "roleFuelLevel" + devIndex

                    if(jsonArray.length < paramCounter+1) {
                        var itemCurrentRole = Object()
                        itemCurrentRole[roleLiters] = valueLiters;
                        itemCurrentRole[roleFuelLevel] = valueFuelLevel;
                        jsonArray.push(itemCurrentRole)
                    } else {
                        var iItem = jsonArray[paramCounter]
                        iItem[roleLiters] = valueLiters;
                        iItem[roleFuelLevel] = valueFuelLevel;
                    }
                    paramCounter++;
                }
            }
        }
        for(var len=0; len<jsonArray.length; len++) {
            if(tarTabViewMultiple.model.get(len) === undefined) {
                tarTabViewMultiple.currentRow = 0
                tarTabViewMultiple.model.append(jsonArray[len])
            } else {
                tarTabViewMultiple.model.set(len, jsonArray[len])
            }
        }
    }

    function changeDeviceUniqId() {
        changeDevId.open()
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
                    textLine:1
                    widthBody: 155
                    useIcon: true
                    iconCode: "\uF274  "
                }
                MiscElems.TabButtonUp {
                    name: "Конфигурирование"
                    textLine:1
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
                            Row{
                                spacing: 10
                                Rectangle{
                                    width: 150
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: levelValueLabel
                                        text: qsTr("Уровень/Объем:")
                                        color: "#888d91"
                                        anchors.left: parent.left
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id:fuelLevelProgress
                                        width: 110
                                        height: 110
                                        anchors.centerIn: parent
                                        penStyle: Qt.RoundCap
                                        dialType: RadialBar.FullDial
                                        progressColor: "#05fff0"
                                        foregroundColor: "transparent"
                                        dialWidth: 15
                                        startAngle: 180
                                        spanAngle: 70
                                        minValue: 0
                                        maxValue: 100
                                        value: 0
                                        textFont {
                                            family: "Halvetica"
                                            italic: false
                                            pointSize: 12
                                        }
                                        suffixText: "%"
                                        textColor: "#888d91"
                                        enabled: devIsConnected
                                    }
                                }

                                Rectangle{
                                    width: 150
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: levelCntLabel
                                        text: qsTr("CNT значение:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id:levelCnt
                                        anchors.centerIn: parent
                                        width: 110
                                        height: 110
                                        penStyle: Qt.RoundCap
                                        dialType: RadialBar.FullDial
                                        progressColor: "#1dc58f"
                                        foregroundColor: "transparent"
                                        dialWidth: 15
                                        startAngle: 180
                                        spanAngle: 70
                                        minValue: 0
                                        maxValue: 5000000
                                        showText: false
                                        value: 0
                                        textFont {
                                            family: "Halvetica"
                                            italic: false
                                            pointSize: 12
                                        }
                                        suffixText: ""
                                        textColor: "#888d91"
                                        enabled: devIsConnected
                                        onValueChanged: {
                                            levelCntValueCustom.text = value
                                        }
                                        Text {
                                            id:levelCntValueCustom
                                            text:"NA"
                                            color: parent.textColor
                                            font.pointSize: 12
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                }

                                Rectangle{
                                    width: 150
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: levelTempLabel
                                        text: qsTr("Температура:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id:levelTemp
                                        anchors.centerIn: parent
                                        width: 110
                                        height: 110
                                        penStyle: Qt.RoundCap
                                        dialType: RadialBar.FullDial
                                        progressColor: "#f329b8"
                                        foregroundColor: "transparent"
                                        dialWidth: 15
                                        startAngle: 180
                                        spanAngle: 70
                                        minValue: 0
                                        maxValue: 80
                                        value: 0
                                        textFont {
                                            family: "Halvetica"
                                            italic: false
                                            pointSize: 12
                                        }
                                        suffixText: "°C"
                                        textColor: "#888d91"
                                        enabled: devIsConnected
                                    }
                                }

                                Rectangle{
                                    width: 150
                                    height: 150
                                    radius: 15
                                    color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    Label {
                                        id: levelFreqLabel
                                        text: qsTr("Частота:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id:levelFreq
                                        anchors.centerIn: parent
                                        width: 110
                                        height: 110
                                        penStyle: Qt.RoundCap
                                        dialType: RadialBar.FullDial
                                        progressColor: "#f3c129"
                                        foregroundColor: "transparent"
                                        dialWidth: 15
                                        startAngle: 180
                                        spanAngle: 70
                                        minValue: 0
                                        maxValue: 15000
                                        value: 0
                                        textFont {
                                            family: "Halvetica"
                                            italic: false
                                            pointSize: 12
                                        }
                                        suffixText: "Hz"
                                        textColor: "#888d91"
                                        enabled: devIsConnected
                                    }
                                }
                            }
                        }
                        Column {
                            Rectangle {
                                height: 300
                                width: column.width// - 50
                                radius: 15
                                color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                ChartView {
                                    id: chartCurrentValue
                                    anchors.fill: parent
                                    theme: ChartView.ChartThemeLight
                                    title: "Частота (Гц)"
                                    backgroundColor: devIsConnected ? "#ffffff" : "#d9d9d9"
                                    antialiasing: true
                                    property int graphLength: 1
                                    property int graphAmplitudeMax: 1
                                    property var dataList: []
                                    ValueAxis {
                                        id: chartCurrentValueLinesX
                                        min: 0
                                        max: chartCurrentValue.graphLength
                                        tickCount: 5
                                        labelsVisible: false
                                    }
                                    ValueAxis {
                                        id: chartCurrentValueLinesY
                                        min: 0
                                        max: chartCurrentValue.graphAmplitudeMax
                                        tickCount: 5
                                    }
                                    LineSeries {
                                        id: chartCurrentValueLines
                                        axisX: chartCurrentValueLinesX
                                        axisY: chartCurrentValueLinesY
                                    }
                                    enabled: devIsConnected
                                }
                            }
                        }


                        Column {
                            Rectangle {
                                id:errorRectangle
                                height: 400
                                width: column.width
                                radius: 15
                                enabled: devIsConnected
                                color: devIsConnected ? "#ffffff" : "#d9d9d9"
                                Column {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 15
                                    spacing: 5

                                    Label {
                                        id: errorsLabel
                                        text: qsTr("Ошибки:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                    }

                                    MiscElems.ButtonRound {
                                        id:readErrors
                                        textLine: 1
                                        widthBody: 150
                                        name:"Считать ошибки"
                                        iconCode: "\uf12a  "
                                        useIcon: true

                                        enabled: devIsConnected
                                        onClicked: {
                                            viewController.setCurrentDevCustomCommand("read current dev errors", [], [])
                                        }
                                    }
                                    Row{
                                        width: 400
                                        height: 30
                                        Label {
                                            id:error1Label
                                            property bool error1: false
                                            text: "Датчик не откалиброван:"
                                        }
                                        Image {
                                            height: 32
                                            width: 32
                                            source: error1Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                        }
                                    }
                                    Column {
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error2Label
                                                text: "Выход за минимальную границу измерения на 10%:"
                                                property bool error2: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error2Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error3Label
                                                text: "Выход за максимальную границу измерения на 10%:"
                                                property bool error3: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error3Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error4Label
                                                text: "Частота измерительного генератора 0 Гц:"
                                                property bool error4: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error4Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error5Label
                                                text: "Ведомый датчик №1 не отвечает:"
                                                property bool error5: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error5Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }

                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error6Label
                                                text: "Ведомый датчик №2 не отвечает:"
                                                property bool error6: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error6Label.error1 === true ? "qrc:/icon/images/icon/bad.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error7Label
                                                text: "Ведомый датчик №3 не отвечает:"
                                                property bool error7: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error7Label.error1 === true ? "qrc:/icon/images/icon/4149.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                        Row{
                                            width: 400
                                            height: 30
                                            Label {
                                                id:error8Label
                                                text: "Ведомый датчик №4 не отвечает:"
                                                property bool error8: false
                                            }
                                            Image {
                                                height: 32
                                                width: 32
                                                source: error8Label.error1 === true ? "qrc:/icon/images/icon/4149.png" : "qrc:/icon/images/icon/normal.png"
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Column {
                            Rectangle {
                                height: 250
                                width: column.width
                                color: "#ffffff"
                                radius: 15
                                Column {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 15
                                    spacing: 20

                                    Label {
                                        text: qsTr("Сообщения:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                    }
                                    ListView {
                                        id: logListView
                                        clip: true
                                        height: 200
                                        width: column.width - 50

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
                                                color: "transparent"
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
                        Rectangle {
                            height: 100
                            width: column.width
                            color: "#ffffff"
                            radius: 15
                        }
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
                                name: "Общее"
                                textLine:1
                                widthBody: 100
                                useIcon: true
                                iconCode: "\uF015  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Калибровка\nMinMax"
                                textLine:2
                                widthBody: 120
                                useIcon: true
                                iconCode: "\uF492  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Фильтрация"
                                textLine:1
                                widthBody: 115
                                useIcon: true
                                iconCode: "\uF0B0  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Температурная\nкомпенсация"
                                textLine:2
                                widthBody: 135
                                useIcon: true
                                iconCode: "\uF2C9  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Ведущий\nведомый"
                                textLine:2
                                widthBody: 110
                                useIcon: true
                                iconCode: "\uf5ee  "
                            }
                            MiscElems.TabButtonUp {
                                name: "Тарировка"
                                textLine:1
                                widthBody: 110
                                useIcon: true
                                iconCode: "\uF080  "
                            }
                        }
                    }

                    SwipeView {
                        id: stackSubProperty
                        currentIndex: tabSubProperty.currentIndex
                        clip: true
                        width: parent.width
                        height: parent.height - subBarup.height
                        Component{
                            id: columnComponent
                            Controls_1_4.TableViewColumn{width: 30 }
                        }
                        onCurrentIndexChanged: {
                            if(stackSubProperty.currentItem == itemDevTarir) {
                                // first check what not device in the tarClass
                                // when show dialog and add it
                                var tarirDevType = viewController.getStayedDevTarrir_DevProperty("type")
                                var tarirDevId =  viewController.getStayedDevTarrir_DevProperty("id")
                                var tarirDevSn = viewController.getStayedDevTarrir_DevProperty("sn")
                                if(viewController.getStayedDevTarrirCount()) {
                                    dialogTarNotEmpty.open()
                                }
                                for(var tarcount=0; tarcount<tarirDevType.length; tarcount++) {
                                    viewController.removeTarrirDev(tarirDevType[tarcount], tarirDevId[tarcount])
                                }
                                // add current
                                var keys = viewController.getCurrentDevPropertyKey()
                                var values = viewController.getCurrentDevPropertyValue()
                                var devType = ""
                                var devId = ""
                                for(var i=0; i<keys.length; i++) {
                                    if(keys[i] === "devTypeName"){
                                        devType = values[i]
                                    }
                                    if(keys[i] === "id"){
                                        devId = values[i]
                                    }
                                }
                                viewController.addTarrirDev(devType, devId)
                                timerAffterChangeTarTable.start()
                            }
                        }
                        Dialog {
                            id: dialogTarNotEmpty
                            visible: false
                            title: "Тарировка"
                            standardButtons: StandardButton.Close
                            Rectangle {
                                color: "transparent"
                                implicitWidth: 500
                                implicitHeight: 200
                                TextEdit{
                                    text: "Обнаружены не сохраненные данные в процессе тарировки\nПроводить тарировку можно только на одной открытой вкладке\n(Последней открытой)"
                                    color: "black"
                                    anchors.centerIn: parent
                                    readOnly: true
                                }
                            }
                        }
                        Timer {
                            id: timerAffterChangeTarTable
                            interval: 100
                            running: false
                            repeat: false
                            onTriggered: {
                                remakeTarTable()
                                remakeTarTableChart()
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
                                    Row{
                                        height: 100
                                        width: 500
                                        Rectangle {
                                            id:changeIdRect
                                            width: 500
                                            height: 100
                                            color: "#fdfdfb"
                                            Column{
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 10
                                                Label {
                                                    text: "Смена сетевого адреса:"
                                                }
                                                Button {
                                                    text: "Сменить адрес"
                                                    id: changeIdAddr
                                                    width: 300
                                                    height: 30
                                                    enabled: (devIsConnected && devIsReady)
                                                    onClicked: {
                                                        changeDeviceUniqId()
                                                    }
                                                }
                                            }
                                        }
                                        Button {
                                            text: "Считать настройки"
                                            id:readSetingsButton_1
                                            width: 180
                                            height: 50
                                            enabled: (devIsConnected && devIsReady)
                                            onClicked: {
                                                viewController.setCurrentDevCustomCommand("get current dev settings", [], [])
                                            }
                                        }
                                        Button {
                                            id:writeSettingsButton_1
                                            text: "Записать настройки"
                                            width: 180
                                            height: 50
                                            enabled: false
                                            onClicked: {
                                                writeSettings()
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Самостоятельная выдача данных:"
                                            }
                                            ComboBox {
                                                id: periodicSendType
                                                height: 25
                                                width: 300
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
                                                onCurrentIndexChanged: {
                                                    if(periodicSendType.currentIndex != 0) {
                                                        periodicSendTime.enabled = true
                                                    } else {
                                                        periodicSendTime.enabled = false
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Период выдачи данных (0-255), с:"
                                            }
                                            SpinBox {
                                                id:periodicSendTime
                                                height: 25
                                                width: 200
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Мин. значение уровня (0-1023):"
                                            }
                                            SpinBox {
                                                id:minLevelValue
                                                height: 25
                                                width: 200
                                                to: 4095
                                                from: 0
                                                value: 0
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Макс.значение уровня (0-4095):"
                                            }
                                            SpinBox {
                                                id:maxLevelValue
                                                height: 25
                                                width: 200
                                                to: 4095
                                                from: 0
                                                value: 0
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Параметр в выходном сообщении датчика:"
                                            }
                                            ComboBox {
                                                id: typeOutMessage
                                                height: 25
                                                width: 300
                                                model: ListModel {
                                                    ListElement {
                                                        text: "Относительный уровень"
                                                    }
                                                    ListElement {
                                                        text: "Объем (по таблице тарировки)"
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Скорость обмена по RS232:"
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
                                        }
                                    }

                                    Rectangle {
                                        width: 500
                                        height: 100
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Скорость обмена по RS485:"
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
                                    Row{
                                        width: 500
                                        height: 150
                                        Rectangle {
                                            id:setScaleFuelLabel
                                            width: 500
                                            height: 150
                                            color: "#fdfdfb"
                                            Column{
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 10
                                                Label {
                                                    id:emptyFullLabel
                                                    text: qsTr("Задание границ измерения:")
                                                }
                                                Button {
                                                    id: buttonEmpty
                                                    text: "Пустой"
                                                    width: 300
                                                    height: 30
                                                    enabled: (devIsConnected && devIsReady)
                                                    onClicked: {
                                                        dialogLevelSetEmpty.open()
                                                    }
                                                    Dialog {
                                                        id: dialogLevelSetEmpty
                                                        visible: false
                                                        title: "Смена уровня Min-Max"
                                                        standardButtons: StandardButton.Close | StandardButton.Ok
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
                                                            viewController.setCurrentDevCustomCommand("set current level value as min", [], [])
                                                            close()
                                                        }
                                                    }
                                                }
                                                Button {
                                                    id: buttonFull
                                                    text: "Полный"
                                                    width: 300
                                                    height: 30
                                                    enabled: (devIsConnected && devIsReady)
                                                    onClicked: {
                                                        dialogLevelSetFull.open()
                                                    }
                                                    Dialog {
                                                        id: dialogLevelSetFull
                                                        visible: false
                                                        title: "Смена уровня Min-Max"
                                                        standardButtons: StandardButton.Close | StandardButton.Ok
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
                                                            viewController.setCurrentDevCustomCommand("set current level value as max", [], [])
                                                            close()
                                                        }
                                                    }
                                                }
                                                Button {
                                                    id: buttonEdit
                                                    width: 300
                                                    height: 30
                                                    text: "Редактировать"
                                                    enabled: false
                                                }
                                            }
                                        }
                                        Button {
                                            text: "Считать настройки"
                                            id:readSetingsButton_2
                                            width: 180
                                            height: 50
                                            enabled: (devIsConnected && devIsReady)
                                            onClicked: {
                                                viewController.setCurrentDevCustomCommand("get current dev settings", [], [])
                                            }
                                        }
                                        Button {
                                            id:writeSettingsButton_2
                                            text: "Записать настройки"
                                            width: 180
                                            height: 50
                                            enabled: false
                                            onClicked: {
                                                writeSettings()
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 150
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Тип жидкости"
                                            }
                                            ComboBox {
                                                id: typeFuel
                                                height: 25
                                                width: 300
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
                                    Row{
                                        width: 500
                                        height: 80
                                        Rectangle {
                                            id:typeInterpolationRect
                                            width: 500
                                            height: 80
                                            color: "#fdfdfb"
                                            Column{
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 10
                                                Label {
                                                    text: "Тип интерполяции:"
                                                }
                                                ComboBox {
                                                    id: typeInterpolation
                                                    height: 25
                                                    width: 300
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
                                        Button {
                                            text: "Считать настройки"
                                            id:readSetingsButton_3
                                            width: 180
                                            height: 50
                                            enabled: (devIsConnected && devIsReady)
                                            onClicked: {
                                                viewController.setCurrentDevCustomCommand("get current dev settings", [], [])
                                            }
                                        }
                                        Button {
                                            id:writeSettingsButton_3
                                            text: "Записать настройки"
                                            width: 180
                                            height: 50
                                            enabled: false
                                            onClicked: {
                                                writeSettings()
                                            }
                                        }
                                    }
                                    //1
                                    Rectangle {
                                        id:typeFiltrationRectangle
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Тип фильтрации:"
                                            }
                                            ComboBox {
                                                id: typeFiltration
                                                height: 25
                                                width: 300
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
                                                onCurrentIndexChanged: {
                                                    if(typeFiltration.currentIndex == 0) {
                                                        filterAvarageValueSec.enabled = false
                                                        filterLenghtMediana.enabled = false
                                                        filterValueQ.enabled = false
                                                        filterValueR.enabled = false
                                                    } else if(typeFiltration.currentIndex == 1) {
                                                        filterAvarageValueSec.enabled = true
                                                        filterLenghtMediana.enabled = false
                                                        filterValueQ.enabled = false
                                                        filterValueR.enabled = false
                                                    } else if(typeFiltration.currentIndex == 2) {
                                                        filterAvarageValueSec.enabled = true
                                                        filterLenghtMediana.enabled = true
                                                        filterValueQ.enabled = false
                                                        filterValueR.enabled = false
                                                    } else if(typeFiltration.currentIndex == 3) {
                                                        filterAvarageValueSec.enabled = false
                                                        filterLenghtMediana.enabled = false
                                                        filterValueQ.enabled = true
                                                        filterValueR.enabled = true
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    //2
                                    Rectangle {
                                        id:typeAvarageRectangle
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Время усреднения (0-21), с:"
                                            }
                                            SpinBox {
                                                id: filterAvarageValueSec
                                                height: 25
                                                width: 200
                                            }
                                        }
                                    }
                                    //3
                                    Rectangle {
                                        id:lenMedianaRectangle
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Длина медианы (0-7):"
                                            }
                                            SpinBox {
                                                id: filterLenghtMediana
                                                height: 25
                                                width: 200
                                            }
                                        }
                                    }
                                    //4
                                    Rectangle {
                                        id:covairachiaRectangle
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: "Ковариация шума процесса (Q):"
                                            }
                                            SpinBox {
                                                id: filterValueQ
                                                height: 25
                                                width: 200
                                            }
                                        }
                                    }
                                    //5
                                    Rectangle {
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Label {
                                            text: "Ковариация шума измерения (R):"
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                        }
                                        SpinBox {
                                            id: filterValueR
                                            height: 25
                                            width: 200
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.topMargin: 10
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
                                    //1
                                    Row {
                                        width: 500
                                        height: 100
                                        Rectangle {
                                            id:termocomRectangle
                                            width: 500
                                            height: 100
                                            color: "#fdfdfb"
                                            Column{
                                                spacing: 10
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                Label {
                                                    text: qsTr("Температурная компенсация линейного расширения топлива\nРежим:")
                                                }
                                                ComboBox {
                                                    id: typeTempCompensation
                                                    width: 300
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
                                                    onCurrentIndexChanged: {
                                                        if(typeTempCompensation.currentIndex == 7) {
                                                            k1.enabled = true
                                                            k2.enabled = true
                                                        } else {
                                                            k1.enabled = false
                                                            k2.enabled = false
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        Button {
                                            text: "Считать настройки"
                                            id:readSetingsButton_4
                                            width: 180
                                            height: 50
                                            enabled: (devIsConnected && devIsReady)
                                            onClicked: {
                                                viewController.setCurrentDevCustomCommand("get current dev settings", [], [])
                                            }
                                        }
                                        Button {
                                            id:writeSettingsButton_4
                                            text: "Записать настройки"
                                            width: 180
                                            height: 50
                                            enabled: false
                                            onClicked: {
                                                writeSettings()
                                            }
                                        }
                                    }
                                    //2
                                    Rectangle {
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: qsTr("K1:")
                                            }
                                            TextField {
                                                id: k1
                                                text: "0.0"
                                                height: 25
                                                width: 300
                                            }
                                        }
                                    }
                                    //3
                                    Rectangle {
                                        width: 500
                                        height: 80
                                        color: "#fdfdfb"
                                        Column {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                text: qsTr("K2:")
                                            }
                                            TextField {
                                                id: k2
                                                text: "0.0"
                                                height: 25
                                                width: 300
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
                                    //1
                                    Row {
                                        width: 500
                                        height: 130
                                        Rectangle {
                                            id:setSlaveMasterModeRectangle
                                            width: parent.width
                                            height: parent.height
                                            color: "#fdfdfb"
                                            Column {
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                spacing: 10
                                                Label {
                                                    text: "Режим ведущий/ведомый:"
                                                    id:labelSlaveModes
                                                }
                                                ComboBox {
                                                    id: masterSlaveModes
                                                    width: 200
                                                    height: 30
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
                                                            //masterSlavesAddresRectange.enabled = true
                                                        } else {
                                                            //masterSlavesAddresRectange.enabled = false
                                                            masterSlaveFullCountes.value = 0
                                                        }
                                                    }
                                                }
                                                Label {
                                                    id: masterSlaveModeCountAllLabel
                                                    text: "Количество ведомых:"
                                                }
                                                SpinBox {
                                                    id: masterSlaveFullCountes
                                                    width: 200
                                                    height: 25
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
                                            }
                                        }

                                        Button {
                                            text: "Считать настройки"
                                            id:readSetingsButton_5
                                            width: 180
                                            height: 50
                                            enabled: (devIsConnected && devIsReady)
                                            onClicked: {
                                                viewController.setCurrentDevCustomCommand("get current dev settings", [], [])
                                            }
                                        }
                                        Button {
                                            id:writeSettingsButton_5
                                            text: "Записать настройки"
                                            width: 180
                                            height: 50
                                            enabled: false
                                            onClicked: {
                                                writeSettings()
                                            }
                                        }
                                    }
                                    Rectangle {
                                        width: 500
                                        height: 250
                                        color: "#fdfdfb"
                                        Column{
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            spacing: 10
                                            Label {
                                                id: masterSlaveAddress_1
                                                text: "Адрес ведомого №1"
                                            }
                                            SpinBox {
                                                id: masterSlaveSlaveId_1
                                                from: 1
                                                to: 254
                                                height: 25
                                                width: 200
                                            }
                                            Label {
                                                text: "Адрес ведомого №2"
                                                id: masterSlaveAddress_2
                                            }
                                            SpinBox {
                                                id: masterSlaveSlaveId_2
                                                height: 25
                                                from: 1
                                                to: 254
                                                width: 200
                                            }
                                            Label {
                                                text: "Адрес ведомого №3"
                                                id: masterSlaveAddress_3
                                            }
                                            SpinBox {
                                                id: masterSlaveSlaveId_3
                                                height: 25
                                                from: 1
                                                to: 254
                                                width: 200
                                            }
                                            Label {
                                                text: "Адрес ведомого №4"
                                                id: masterSlaveAddress_4
                                            }
                                            SpinBox {
                                                id: masterSlaveSlaveId_4
                                                height: 25
                                                from: 1
                                                width: 200
                                                to: 254
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Item {
                            id:itemDevTarir
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
                                        id:tarRowRoot1
                                        spacing: 10
                                        Rectangle {
                                            radius: 20
                                            width: stackSubProperty.width - 30
                                            height: stackSubProperty.height - 10
                                            color: "transparent"
                                            Rectangle {
                                                id:tarTabRectangleMultiple
                                                anchors.left: parent.left
                                                anchors.top: parent.top
                                                height: parent.height - 70
                                                width: parent.width / 2
                                                Controls_1_4.TableView {
                                                    id:tarTabViewMultiple
                                                    anchors.left: parent.left
                                                    anchors.top: parent.top
                                                    height: parent.height / 2
                                                    width: parent.width

                                                    model: ListModel {}
                                                    onCurrentRowChanged: {
                                                        tarTabViewMultiple.selection.clear()
                                                        tarTabViewMultiple.selection.select(tarTabViewMultiple.currentRow)
                                                    }

                                                    rowDelegate: Rectangle {
                                                        SystemPalette {
                                                            id: systemPaletteMultiple
                                                            colorGroup: SystemPalette.Active
                                                        }
                                                        color: {
                                                            var baseColor = styleData.alternate ? systemPaletteMultiple.alternateBase : systemPaletteMultiple.base
                                                            return styleData.selected ? "orange" : baseColor
                                                        }
                                                    }
                                                }
                                                ChartView {
                                                    id: chartTarTableMultiple
                                                    anchors.top: tarTabViewMultiple.bottom
                                                    anchors.topMargin: 5
                                                    anchors.left: parent.left
                                                    height: parent.height / 2
                                                    width: parent.width
                                                    theme: ChartView.ChartThemeBlueCerulean
                                                    clip: true
                                                    antialiasing: true
                                                    title: "Отношение уровня к объему"
                                                    property int chartTarTableLength: 1
                                                    property int chartTarTableAmplitudeMax: 1
                                                    ValueAxis {
                                                        id: chartTarTableAxisXMultiple
                                                        min: 0
                                                        max: chartTarTableMultiple.chartTarTableLength
                                                        tickCount: 5
                                                    }
                                                    ValueAxis {
                                                        id: chartTarTableAxisYMultiple
                                                        min: 0
                                                        max: chartTarTableMultiple.chartTarTableAmplitudeMax
                                                        tickCount: 5
                                                    }
                                                }
                                                Rectangle {
                                                    id:tarTabRectangleCurrentValuesMultiple
                                                    anchors.left: tarTabRectangleMultiple.right
                                                    anchors.leftMargin: 10
                                                    anchors.top: parent.top
                                                    radius: 20
                                                    width: parent.width - 5
                                                    height: parent.height / 2// + 40
                                                    color: "#ffffff"

                                                    ListView {
                                                        id: tarListDevice
                                                        clip: true
                                                        height: parent.height
                                                        width: parent.width - 10
                                                        ScrollBar.vertical: ScrollBar {
                                                            width: 20
                                                        }
                                                        delegate: Item {
                                                            id: tarListDeviceDelegate
                                                            height: 70
                                                            width: parent.width

                                                            Rectangle {
                                                                id:tarTabRectangleCurrLevelMultiple
                                                                anchors.left: parent.left
                                                                anchors.leftMargin: 2
                                                                anchors.top: parent.top
                                                                radius: 20
                                                                width: parent.width / 2 - 15
                                                                height: parent.height
                                                                color: "transparent"

                                                                Label {
                                                                    id: levelTarCurrCntLabelMultiple
                                                                    text: qsTr("%1\nSN[%2]\nID[%3]").arg(model.devTyp).arg(model.devSn).arg(model.devId)
                                                                    anchors.left: parent.left
                                                                    color: "#888d91"
                                                                    anchors.leftMargin: 15
                                                                    anchors.right: parent.right
                                                                    anchors.rightMargin: 0
                                                                }
                                                                TextField {
                                                                    id:levelTarCurrCntValueMultiple
                                                                    anchors.left: levelTarCurrCntLabelMultiple.right
                                                                    width: 120
                                                                    height: 50
                                                                    background: Rectangle {
                                                                        color: "#05fF00"
                                                                        height: parent.height
                                                                    }
                                                                    text: model.valueCnt
                                                                    readOnly: true
                                                                }
                                                                TextField {
                                                                    id:levelTarCurrCntValuesMultiple
                                                                    anchors.left: levelTarCurrCntValueMultiple.right
                                                                    width: 120
                                                                    height: 50
                                                                    background: Rectangle {
                                                                        color: "#080ff0"
                                                                        height: parent.height
                                                                    }
                                                                    text: model.valueFuelLevel
                                                                    color: "white"
                                                                    readOnly: true
                                                                }
                                                            }
                                                        }
                                                        model: ListModel {
                                                            id: logItemModel
                                                        }
                                                    }
                                                }
                                                Rectangle {
                                                    color: "#ffffff"
                                                    anchors.top: tarTabRectangleCurrentValuesMultiple.bottom
                                                    anchors.left: tarTabRectangleMultiple.right
                                                    anchors.leftMargin: 10
                                                    radius: 20
                                                    width: parent.width - 5
                                                    anchors.topMargin: 10
                                                    height: parent.height / 2 - 10
                                                    ChartView {
                                                        id: chartTarCurrentValuesMultiple
                                                        anchors.fill: parent
                                                        theme: ChartView.ChartThemeLight
                                                        title: "Уровень/Объем"
                                                        antialiasing: true
                                                        property int graphLength: 1
                                                        property int graphAmplitudeMax: 1
                                                        backgroundColor: "transparent"
                                                        property alias animateColorUp: animateColorUpMultiple
                                                        property alias animateColorDown: animateColorDownMultiple
                                                        PropertyAnimation {id: animateColorUpMultiple; target: chartTarCurrentValuesMultiple; properties: "backgroundColor"; to: "#d9d9d9"; duration: 1000
                                                            onStopped: {
                                                                chartTarCurrentValuesMultiple.animateColorDown.start()
                                                            }
                                                            onStarted: {
                                                                isNoiseDetected = true
                                                            }
                                                        }
                                                        PropertyAnimation {id: animateColorDownMultiple; target: chartTarCurrentValuesMultiple; properties: "backgroundColor"; to: "transparent"; duration: 1000
                                                            onStopped: {
                                                                isNoiseDetected = false
                                                            }
                                                        }

                                                        ValueAxis {
                                                            id: currentTarChartAxisXMultiple
                                                            min: -0.5
                                                            max: chartTarCurrentValuesMultiple.graphLength
                                                            tickCount: 5
                                                        }
                                                        ValueAxis {
                                                            id: currentTarChartAxisYMultiple
                                                            min: -0.5
                                                            max: chartTarCurrentValuesMultiple.graphAmplitudeMax
                                                            tickCount: 5
                                                        }
                                                        enabled: devIsConnected
                                                    }
                                                }
                                            }
                                            Rectangle {
                                                anchors.top: tarTabRectangleMultiple.bottom
                                                anchors.topMargin: 10
                                                radius: 20
                                                width: stackSubProperty.width -15
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    MiscElems.ButtonRound {
                                                        id:tarBatButtonsMultiple
                                                        textLine:2
                                                        widthBody: 150
                                                        name: qsTr("Добавить\nтекущее значение")
                                                        useIcon: true
                                                        iconCode: "\uF0FE  "
                                                        enabled: (devIsConnected && devIsReady)
                                                        onClicked: {
                                                            if(!isNoiseDetected) {
                                                                addTarStepValue(tarTabViewMultiple.currentRow)
                                                            } else {
                                                                dialogAddTarValueWhenNoiseDetectedMultiple.open()
                                                            }
                                                        }

                                                        Dialog {
                                                            id: dialogAddTarValueWhenNoiseDetectedMultiple
                                                            title: "Добавление значения в таблицу"
                                                            standardButtons: StandardButton.Close | StandardButton.Ok
                                                            Rectangle {
                                                                color: "transparent"
                                                                implicitWidth: 500
                                                                implicitHeight: 50
                                                                Text {
                                                                    text: "Обнаружен шум показаний\nДействительно добавить это значение?"
                                                                    color: "black"
                                                                    anchors.centerIn: parent
                                                                }
                                                            }
                                                            onApply: {
                                                                addTarStepValue(tarTabViewMultiple.currentRow)
                                                                close()
                                                            }
                                                        }
                                                    }
                                                    MiscElems.ButtonRound {
                                                        id:tarTabRemoveStepMultiple
                                                        textLine:2
                                                        widthBody: 100
                                                        name: qsTr("Удалить\nзначение")
                                                        useIcon: true
                                                        iconCode: "\uF1f8  "
                                                        Dialog {
                                                            id: dialogRemoveTarTableRowMultiple
                                                            title: "Удаление записи таблицы"
                                                            standardButtons: StandardButton.Ok
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
                                                            if(tarTabViewMultiple.currentRow === -1) {
                                                                dialogRemoveTarTableRowMultiple.open()
                                                            } else {
                                                                removeTarStepValue(tarTabViewMultiple.currentRow)
                                                                timerAffterRefrashTarTable.start()
                                                            }
                                                        }
                                                    }
                                                    MiscElems.ButtonRound {
                                                        id:tarTabRemoveAddDeviceMultiple
                                                        textLine:2
                                                        widthBody: 165
                                                        useIcon: true
                                                        iconCode: "\uF0FE  "
                                                        name: qsTr("Добавить/Удалить\nустройство")
                                                        onClicked: {
                                                            addDeviceTarirDialog.open()
                                                        }
                                                        Timer {
                                                            id: timerAffterAddRemoveDevTarTable
                                                            interval: 100
                                                            running: false
                                                            repeat: false
                                                            onTriggered: {
                                                                remakeTarTable()
                                                                remakeTarTableChart()
                                                            }
                                                        }
                                                    }
                                                    MiscElems.ButtonRound {
                                                        id:tarTabReadTableMultiple
                                                        textLine: 2
                                                        name:"Считать\nтаблицу"
                                                        useIcon: true
                                                        iconCode: "\uF093  "
                                                        enabled: (devIsConnected && devIsReady)
                                                        onClicked: {
                                                            dialogReadTarTableMultiple.open()
                                                        }
                                                        Dialog {
                                                            id: dialogReadTarTableMultiple
                                                            visible: false
                                                            title: "Чтение записей таблицы из устройства"
                                                            standardButtons: StandardButton.Close | StandardButton.Ok
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
                                                                remakeTarTable()
                                                                viewController.sendReqGetTarrirAllDev()
                                                                close()
                                                            }
                                                        }
                                                    }
                                                    MiscElems.ButtonRound {
                                                        id:tarTabWriteTableMultiple
                                                        textLine: 2
                                                        name:"Записать\nтаблицу"
                                                        useIcon: true
                                                        iconCode: "\uF0C7  "
                                                        enabled: (devIsConnected && devIsReady)
                                                        Dialog {
                                                            id: dialogWriteTarTableMultipleRequest
                                                            visible: false
                                                            title: "Запись таблицы"
                                                            standardButtons: StandardButton.Close | StandardButton.Ok
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
                                                        Dialog {
                                                            id: dialogWriteTarTableMultipleWarningOverSize
                                                            visible: false
                                                            title: "Запись таблицы"
                                                            standardButtons: StandardButton.Ok
                                                            Rectangle {
                                                                color: "transparent"
                                                                implicitWidth: 500
                                                                implicitHeight: 50
                                                                Text {
                                                                    text: "Данных больше размера памяти в устройстве\nЗапись не возможна"
                                                                    color: "black"
                                                                    anchors.centerIn: parent
                                                                }
                                                            }
                                                            onApply: {
                                                                close()
                                                            }
                                                        }
                                                        Dialog {
                                                            id: dialogWriteTarTableMultipleWarningEmpty
                                                            visible: false
                                                            title: "Запись таблицы"
                                                            standardButtons: StandardButton.Ok
                                                            Rectangle {
                                                                color: "transparent"
                                                                implicitWidth: 500
                                                                implicitHeight: 50
                                                                Text {
                                                                    text: "Нет данных для записи!"
                                                                    color: "black"
                                                                    anchors.centerIn: parent
                                                                }
                                                            }
                                                            onApply: {
                                                                close()
                                                            }
                                                        }
                                                        onClicked: {
                                                            if(tarTabViewMultiple.model.count > 0) {
                                                                if(tarTabViewMultiple.model.count < 30) {
                                                                    dialogWriteTarTableMultipleRequest.open()
                                                                } else {
                                                                    dialogWriteTarTableMultipleWarningOverSize.open()
                                                                }
                                                            } else {
                                                                dialogWriteTarTableMultipleWarningEmpty.open()
                                                            }
                                                        }
                                                    }
                                                    MiscElems.ButtonRound {
                                                        id:tarTabTableExportMultiple
                                                        textLine: 2
                                                        name:"Выгрузить\n.csv"
                                                        useIcon: true
                                                        iconCode: "\uF093  "
                                                        widthBody: 110
                                                        FileDialog {
                                                            id: dialogExportTarTableMultiple
                                                            folder: shortcuts.home
                                                            selectMultiple: false
                                                            selectFolder: false
                                                            title: "Save to file"
                                                            nameFilters: [ "All files (*)" ]
                                                            selectExisting: false
                                                            onAccepted: {
                                                                if(dialogExportTarTableMultiple.selectExisting == true) {
                                                                    console.log(dialogExportTarTableMultiple.fileUrl)
                                                                }
                                                                else {
                                                                    console.log(dialogExportTarTableMultiple.fileUrl)
                                                                    saveTarTableToCsv(dialogExportTarTableMultiple.fileUrl)
                                                                }
                                                            }
                                                        }
                                                        onClicked: {
                                                            dialogExportTarTableMultiple.open()
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
            }
        }
        Rectangle {
            id:busyIndicator
            width: 350
            height: 200
            radius: 20
            property string message: "Ожидание ответа..."
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            visible: ((devIsConnected) && (devIsReady)) ? false : true
            color: "transparent"
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: 20
                BusyIndicator {
                    id:waitReadyIndicator
                    width: 110
                    height: 110
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: busyIndicator.message
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    ChangeDevIdName {
        visible: false
        id:changeDevId
    }

    Dialog {
        id: messageDialog
        visible: false
        property string headerTitile: ""
        property string message: ""
        title: headerTitile
        width: 500
        height: 150
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Text {
                text: messageDialog.message
                color: "black"
                anchors.centerIn: parent
            }
        }
        onAccepted: {
            close()
        }
    }

    AddDeviceTarirDialog {
        id:addDeviceTarirDialog
        onAccepted: {
            console.log("AddDeviceTarirDialog-accepted = " + deviceTypeName.length + deviceId.length + deviceSerialNumber.length)
            var tarirDevType = viewController.getStayedDevTarrir_DevProperty("type")
            var tarirDevId =  viewController.getStayedDevTarrir_DevProperty("id")
            var tarirDevSn = viewController.getStayedDevTarrir_DevProperty("sn")
            //
            for(var tarcount=0; tarcount<tarirDevType.length; tarcount++) {
                viewController.removeTarrirDev(tarirDevType[tarcount], tarirDevId[tarcount])
            }
            // обновляем таблицу dev
            for(var devcount=0; devcount<deviceId.length; devcount++) {
                viewController.addTarrirDev(deviceTypeName[devcount], deviceId[devcount])
            }
            timerAffterAddRemoveDevTarTable.start()
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
