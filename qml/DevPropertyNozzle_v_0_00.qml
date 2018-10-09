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
    //    property alias messageMinMaxWriteOk: messageMinMaxWriteOk
    //    property alias messageReadSettingsOk: messageReadSettingsOk
    //    property alias messageWriteSettingsOk: messageWriteSettingsOk
    //    property alias messageReadErrorsOk: messageReadErrorsOk
    //    property alias messageReadTarTableOk: messageReadTarTableOk

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
    function setDevProperty(listProperty) {
        typeDeviceText.text = listProperty[2]
        snText.text = listProperty[0]
        versionFirmwareText.text = listProperty[3]
        // give settings without request to device (copy allready readed)
        viewController.getCurrentDevSettingsWithoutRequest()
    }
    function setUpdateCurrentValues(data) {
        //        devProperty.isReady = true
        //        var values = viewController.getCurrentDevOtherData()
        //        if(values.length >0) {
        //            //levelValue.text = values[0]
        //            levelProgress.value = values[1]
        //            levelCnt.value = parseInt(values[2])
        //            levelFreq.value = values[3]
        //            levelTemp.value = values[4]
        //        }
        //        //-- noise detect
        //        if(values[5] == true) {
        //            if(chartTarCurrentValuesMultiple.animateColorUp.running == false
        //                    & chartTarCurrentValuesMultiple.animateColorDown.running == false) {
        //                chartTarCurrentValuesMultiple.animateColorUp.start()
        //            }
        //        }
        //        //-- chart
        //        var list = viewController.getCurrentDevChart()
        //        currentChartLines.clear();
        //        chartCurrentValue.graphLength = list.length
        //        chartCurrentValue.graphAmplitudeMax = 0

        //        for(var i=0; i<list.length; i++) {
        //            if(chartCurrentValue.graphAmplitudeMax < list[i]) {
        //                chartCurrentValue.graphAmplitudeMax = list[i];
        //            }
        //        }
        //        for(i=0; i<list.length; i++) {
        //            currentChartLines.append(i, list[i]);
        //        }
        //        logListView.positionViewAtEnd()
    }
    function addLogMessage(codeMessage, message) {
        log.append(message)
    }
    //    function readSettings(devName, key, settings) {
    //        for(var i=0; i<settings.length; i++) {
    //            if(key[i] === "k1_value") {
    //                k1.text = settings[i]
    //            } else if(key[i] === "k2_value") {
    //                k2.text = settings[i]
    //            } else if(key[i] === "typeTempCompensation_value") {
    //                typeTempCompensation.currentIndex = settings[i]
    //            } else if(key[i] === "periodicSendType_value") {
    //                periodicSendType.currentIndex = settings[i]
    //            } else if(key[i] === "periodicSendTime_value") {
    //                periodicSendTime.value = settings[i]
    //            } else if(key[i] === "typeOutMessage_value") {
    //                typeOutMessage.currentIndex = settings[i]
    //            } else if(key[i] === "typeInterpolation_value") {
    //                typeInterpolation.currentIndex = settings[i]
    //            } else if(key[i] === "typeFiltration_value") {
    //                typeFiltration.currentIndex = settings[i]
    //            } else if(key[i] === "filterLenghtMediana_value") {
    //                filterLenghtMediana.value = settings[i]
    //            } else if(key[i] === "filterAvarageValueSec_value") {
    //                filterAvarageValueSec.value = settings[i]
    //            } else if(key[i] === "filterValueR_value") {
    //                filterValueR.value= settings[i]
    //            } else if(key[i] === "filterValueQ_value") {
    //                filterValueQ.value = settings[i]
    //            } else if(key[i] === "minLevelValue_value") {
    //                minLevelValue.value = settings[i]
    //            } else if(key[i] === "maxLevelValue_value") {
    //                maxLevelValue.value = settings[i]
    //            } else if(key[i] === "masterSlaveModes_value") {
    //                masterSlaveModes.currentIndex = settings[i]
    //            } else if(key[i] === "baudrateRs232Values_value") {
    //                baudrateRs232Values.currentIndex = settings[i]
    //            } else if(key[i] === "baudrateRs485Values_value") {
    //                baudrateRs485Values.currentIndex = settings[i]
    //            } else if(key[i] === "masterSlaveFullCountes_value") {
    //                masterSlaveFullCountes.value = settings[i]
    //            } else if(key[i] === "masterSlaveSlaveId_1_value") {
    //                masterSlaveSlaveId_1.value = settings[i]
    //            } else if(key[i] === "masterSlaveSlaveId_2_value") {
    //                masterSlaveSlaveId_2.value = settings[i]
    //            } else if(key[i] === "masterSlaveSlaveId_3_value") {
    //                masterSlaveSlaveId_3.value = settings[i]
    //            } else if(key[i] === "masterSlaveSlaveId_4_value") {
    //                masterSlaveSlaveId_4.value = settings[i]
    //            }
    //        }
    //    }
    //    function writeSettings() {
    //        var settings = [];
    //        var key = [];
    //        key.push("k1_value")
    //        settings.push(k1.text)
    //        key.push("k2_value")
    //        settings.push(k2.text)
    //        key.push("typeTempCompensation_value")
    //        settings.push(typeTempCompensation.currentIndex)
    //        key.push("periodicSendType_value")
    //        settings.push(periodicSendType.currentIndex)
    //        key.push("periodicSendTime_value")
    //        settings.push(periodicSendTime.value)
    //        key.push("typeOutMessage_value")
    //        settings.push(typeOutMessage.currentIndex)
    //        key.push("typeInterpolation_value")
    //        settings.push(typeInterpolation.currentIndex)
    //        key.push("typeFiltration_value")
    //        settings.push(typeFiltration.currentIndex)
    //        key.push("filterLenghtMediana_value")
    //        settings.push(filterLenghtMediana.value)
    //        key.push("filterAvarageValueSec_value")
    //        settings.push(filterAvarageValueSec.value)
    //        key.push("filterValueR_value")
    //        settings.push(filterValueR.value)
    //        key.push("filterValueQ_value")
    //        settings.push(filterValueQ.value)
    //        key.push("minLevelValue_value")
    //        settings.push(minLevelValue.value)
    //        key.push("maxLevelValue_value")
    //        settings.push(maxLevelValue.value)
    //        key.push("masterSlaveModes_value")
    //        settings.push(masterSlaveModes.currentIndex)
    //        key.push("baudrateRs232Values_value")
    //        settings.push(baudrateRs232Values.currentIndex)
    //        key.push("baudrateRs485Values_value")
    //        settings.push(baudrateRs485Values.currentIndex)
    //        key.push("masterSlaveFullCountes_value")
    //        settings.push(masterSlaveFullCountes.value)
    //        key.push("masterSlaveSlaveId_1_value")
    //        settings.push(masterSlaveSlaveId_1.value)
    //        key.push("masterSlaveSlaveId_2_value")
    //        settings.push(masterSlaveSlaveId_2.value)
    //        key.push("masterSlaveSlaveId_3_value")
    //        settings.push(masterSlaveSlaveId_3.value)
    //        key.push("masterSlaveSlaveId_4_value")
    //        settings.push(masterSlaveSlaveId_4.value)

    //        viewController.setCurrentDevSettings(key, settings)
    //    }
    //    function readErrors(devName, errors) {
    //        error1Label.error1 = errors[0]
    //        error2Label.error2 = errors[1]
    //        error3Label.error3 = errors[2]
    //        error4Label.error4 = errors[3]
    //        error5Label.error5 = errors[4]
    //        error6Label.error6 = errors[5]
    //        error7Label.error7 = errors[6]
    //        error8Label.error8 = errors[7]
    //    }
    //    function remakeTarTableChart() {
    //        chartTarTableMultiple.removeAllSeries();
    //        var colorArray = []
    //        colorArray.push("#f34b4b")
    //        colorArray.push("#4bd5f3")
    //        colorArray.push("#f34be1")
    //        colorArray.push("#4bf3c6")
    //        colorArray.push("#4b4bf3")
    //        colorArray.push("#be4bf3")
    //        colorArray.push("#0d8741")

    //        var tarSize = viewController.getStayedDevTarrirCount()
    //        for(var deviceCounter=0; deviceCounter<tarSize; deviceCounter++) {
    //            var roleLiters = "roleLiters" + deviceCounter
    //            var roleFuelLevel = "roleFuelLevel" + deviceCounter
    //            var devId = viewController.getStayedDevTarrir_DevProperty("id")

    //            var maxvalueFuelLevel = 0;
    //            var maxValueLitrs = 0;
    //            var tarArrayLitrs = [];
    //            var tarArrayFuelLevel = [];

    //            for(var itemCounter=0; itemCounter<tarTabViewMultiple.rowCount; itemCounter++) {
    //                var item = tarTabViewMultiple.model.get(itemCounter)
    //                tarArrayLitrs.push(item[roleLiters])
    //                tarArrayFuelLevel.push(item[roleFuelLevel])
    //                if(maxvalueFuelLevel < item[roleFuelLevel]) {
    //                    maxvalueFuelLevel = item[roleFuelLevel]
    //                }
    //                if(maxValueLitrs < item[roleLiters]) {
    //                    maxValueLitrs = item[roleLiters]
    //                }
    //                console.log(roleLiters + " " + item[roleFuelLevel] + "\nValue Litrs=" + item[roleLiters])
    //            }

    //            var line = chartTarTableMultiple.createSeries(ChartView.SeriesTypeLine, "ID" + devId[deviceCounter], chartTarTableAxisXMultiple, chartTarTableAxisYMultiple);
    //            line.color = colorArray[deviceCounter]
    //            chartTarTableAxisXMultiple.min = 0;
    //            chartTarTableAxisXMultiple.max = parseInt(maxValueLitrs)
    //            chartTarTableAxisYMultiple.min = 0;
    //            chartTarTableAxisYMultiple.max = parseInt(maxvalueFuelLevel)

    //            chartTarTableMultiple.chartTarTableAmplitudeMax = parseInt(maxvalueFuelLevel)
    //            chartTarTableMultiple.chartTarTableLength = parseInt(maxValueLitrs)

    //            console.log("MaxLevel =" + chartTarTableMultiple.chartTarTableAmplitudeMax)
    //            for(var i=0; i<tarArrayFuelLevel.length; i++) {
    //                line.append(parseInt(tarArrayLitrs[i]), parseInt(tarArrayFuelLevel[i]));
    //                console.log("Add=" + i + " " + tarArrayLitrs[i])
    //            }
    //        }
    //    }
    //    function addTarStepValue(rowIndex) {
    //        if(rowIndex === -1) {
    //            rowIndex = 0
    //        } else {
    //            rowIndex++
    //        }
    //        // если таблица пустая
    //        // создаем строку и заносим в нее текущие значения по устройствам
    //        // пока не переберем все уст-ва
    //        var itemValue = {}
    //        var devCount = viewController.getStayedDevTarrirCount()
    //        var devId = viewController.getStayedDevTarrir_DevProperty("id")

    //        for(var devIndex=0; devIndex<devCount; devIndex++) {
    //            var valueFuelLevel = 0
    //            var valueLiters = 0
    //            var value = viewController.getTarCurrentDeviceData(devIndex)
    //            var roleLiters = "roleLiters" + devIndex
    //            var roleFuelLevel = "roleFuelLevel" + devIndex

    //            valueFuelLevel = value[0]
    //            if(valueFuelLevel == undefined) {
    //                valueFuelLevel = "0"
    //            }
    //            // попытка взять предыдущее значение литров
    //            // если есть
    //            var lastLiter = tarTabViewMultiple.model.get(rowIndex-1)
    //            if(lastLiter !== undefined) {
    //                valueLiters = lastLiter[roleLiters]
    //                if(valueLiters == undefined) {
    //                    valueLiters = "0"
    //                }
    //                if(valueLiters.length === 0) {
    //                    valueLiters = "0"
    //                }
    //            } else {
    //                valueLiters = value[1]
    //                if(valueLiters == undefined) {
    //                    valueLiters = "0"
    //                }
    //                if(valueLiters.length === 0) {
    //                    valueLiters = "0"
    //                }
    //            }
    //            itemValue[roleLiters] = valueLiters;
    //            itemValue[roleFuelLevel] = valueFuelLevel;
    //        }
    //        if(tarTabViewMultiple.model.get(rowIndex) === undefined) {
    //            tarTabViewMultiple.model.append(itemValue)
    //        } else {
    //            tarTabViewMultiple.model.insert(rowIndex, itemValue)
    //        }
    //        tarTabViewMultiple.currentRow = tarTabViewMultiple.currentRow+1
    //        timerAffterRefrashTarTable.start()
    //    }

    //    function removeTarStepValue(rowIndex) {
    //        // если ничего не выбрано выходим
    //        if(rowIndex >= 0) {
    //            // удаляем строку
    //            tarTabViewMultiple.model.remove(rowIndex)
    //            timerAffterRefrashTarTable.start()
    //        }
    //    }

    //    function remakeTarTable() {
    //        tarTabViewMultiple.model.clear()
    //        tarListDevice.model.clear()
    //        for(var index = tarTabViewMultiple.columnCount-1; index>=0; index--) {
    //            tarTabViewMultiple.removeColumn(index)
    //        }
    //        var tarSize = viewController.getStayedDevTarrirCount()
    //        var devType = []
    //        var devId = []
    //        var devSn = []
    //        devType = viewController.getStayedDevTarrir_DevProperty("type")
    //        devId =  viewController.getStayedDevTarrir_DevProperty("id")
    //        devSn = viewController.getStayedDevTarrir_DevProperty("sn")
    //        for(var i=0; i<tarSize; i++) { // добавляем на list with current data
    //            tarListDevice.model.append({"devTyp":devType[i],"devId":devId[i],"devSn":devSn[i],"valueCnt":"0","valueFuelLevel":"0"})
    //        }
    //        // добавляем в таблицу как столблец для девайса
    //        for(var i2=0; i2<tarSize; i2++) {
    //            var component = {}
    //            component = Qt.createComponent("devPropertyTarTableDelegate.qml");
    //            var tableViewColumn  = component.createObject(tarTabViewMultiple);
    //            tableViewColumn.title = qsTr("Объем[ID-%1]").arg(devId[i2])
    //            tableViewColumn.role = "roleLiters" + i2
    //            tableViewColumn.width = 100
    //            tarTabViewMultiple.addColumn(tableViewColumn)
    //            console.log("addeted1 =" + tableViewColumn.role)
    //            tableViewColumn.valueIsChanged.connect(function(role, text, modelChanged) {
    //                var curRow = tarTabViewMultiple.currentRow
    //                modelChanged[role] = text
    //                tarTabViewMultiple.model.set(curRow, modelChanged)
    //                remakeTarTableChart()
    //            });
    //            tableViewColumn  = component.createObject(tarTabViewMultiple);
    //            tableViewColumn.title = qsTr("Ур.топ-ва[ID-%1]").arg(devId[i2])
    //            tableViewColumn.role = "roleFuelLevel" + i2
    //            tableViewColumn.width = 100
    //            tarTabViewMultiple.addColumn(tableViewColumn)

    //            tableViewColumn.valueIsChanged.connect(function(role, text, modelChanged) {
    //                var curRow = tarTabViewMultiple.currentRow
    //                modelChanged[role] = text
    //                tarTabViewMultiple.model.set(curRow, modelChanged)
    //                remakeTarTableChart()
    //            });
    //            console.log("addeted2 =" + tableViewColumn.role)
    //        }
    //    }
    //    function writeTarTable() {
    //        var devCount = viewController.getStayedDevTarrirCount()
    //        var devType = []
    //        var devId = []
    //        var devSn = []
    //        devType = viewController.getStayedDevTarrir_DevProperty("type")
    //        devId =  viewController.getStayedDevTarrir_DevProperty("id")
    //        devSn = viewController.getStayedDevTarrir_DevProperty("sn")

    //        // считываем данные по ролям
    //        for(var count=0; count<devCount; count++) {
    //            var valueFuelLevel = 0
    //            var valueLiters = 0
    //            var roleLiters = "roleLiters" + count
    //            var roleFuelLevel = "roleFuelLevel" + count
    //            var jsonArrayCnt = []
    //            var jsonArrayLiters = []
    //            // считываем все шаги для одного устройства
    //            var modelTarSize = tarTabViewMultiple.model.count
    //            for(var subCount=0; subCount<modelTarSize; subCount++) {
    //                var values = tarTabViewMultiple.model.get(subCount)
    //                if(values !== undefined) {
    //                    valueLiters = values[roleLiters]
    //                    valueFuelLevel = values[roleFuelLevel]
    //                    if(valueLiters == undefined) {
    //                        valueLiters = "0"
    //                    }
    //                    if(valueFuelLevel == undefined) {
    //                        valueFuelLevel = "0"
    //                    }
    //                } else {
    //                    valueLiters = values[1]
    //                    if(valueLiters == undefined) {
    //                        valueLiters = "0"
    //                    }
    //                    valueFuelLevel = values[0]
    //                    if(valueFuelLevel == undefined) {
    //                        valueFuelLevel = "0"
    //                    }
    //                }
    //                jsonArrayCnt.push(valueFuelLevel)
    //                jsonArrayLiters.push(valueLiters)
    //            }
    //            viewController.setTableFromFrontEnd(devId[count], jsonArrayLiters, jsonArrayCnt)
    //        }
    //        viewController.sendReqWriteTarrirAllDev()
    //    }

    //    function saveTarTableToCsv(pathFile) {
    //        var devCount = viewController.getStayedDevTarrirCount()
    //        var devType = []
    //        var devId = []
    //        var devSn = []
    //        devType = viewController.getStayedDevTarrir_DevProperty("type")
    //        devId =  viewController.getStayedDevTarrir_DevProperty("id")
    //        devSn = viewController.getStayedDevTarrir_DevProperty("sn")

    //        // считываем данные по ролям
    //        for(var count=0; count<devCount; count++) {
    //            var valueFuelLevel = 0
    //            var valueLiters = 0
    //            var roleLiters = "roleLiters" + count
    //            var roleFuelLevel = "roleFuelLevel" + count
    //            var jsonArrayCnt = []
    //            var jsonArrayLiters = []
    //            // считываем все шаги для одного устройства
    //            var modelTarSize = tarTabViewMultiple.model.count
    //            for(var subCount=0; subCount<modelTarSize; subCount++) {
    //                var values = tarTabViewMultiple.model.get(subCount)
    //                if(values !== undefined) {
    //                    valueLiters = values[roleLiters]
    //                    valueFuelLevel = values[roleFuelLevel]
    //                    if(valueLiters == undefined) {
    //                        valueLiters = "0"
    //                    }
    //                    if(valueFuelLevel == undefined) {
    //                        valueFuelLevel = "0"
    //                    }
    //                } else {
    //                    valueLiters = values[1]
    //                    if(valueLiters == undefined) {
    //                        valueLiters = "0"
    //                    }
    //                    valueFuelLevel = values[0]
    //                    if(valueFuelLevel == undefined) {
    //                        valueFuelLevel = "0"
    //                    }
    //                }
    //                jsonArrayCnt.push(valueFuelLevel)
    //                jsonArrayLiters.push(valueLiters)
    //            }
    //            viewController.setTableFromFrontEnd(devId[count], jsonArrayLiters, jsonArrayCnt)
    //        }
    //        viewController.sendReqExportTarrirAllDevToCsv(pathFile)
    //    }

    //    function readTarTable(devCount) {
    //        console.log("readTarTable = " + devCount)
    //        var jsonArray = []
    //        var tarStepMax = viewController.getTarMaxCountStep()
    //        while(tarStepMax >0) {
    //            jsonArray.push({});
    //            tarStepMax--
    //        }
    //        // пока не переберем все уст-ва
    //        for(var devIndex=0; devIndex<devCount; devIndex++) {
    //            var table = viewController.getTableAtDevice(devIndex)
    //            var parity = 0
    //            var rowIndex = 0
    //            // перебираем таблицу уст-ва
    //            var valueFuelLevel = 0
    //            var valueLiters = 0
    //            var stepCount = viewController.getTarMaxCountStep() *2 // it pair
    //            if(stepCount === 0 | stepCount === undefined) {
    //                messageReadTarTableEmpty.open()
    //            }
    //            console.log("getTable =" + table.length)

    //            for(var devTableRow=0; devTableRow<stepCount; devTableRow++) {
    //                if(parity == 0) {
    //                    parity = 1;
    //                    valueLiters = table[devTableRow]
    //                    if(valueLiters == undefined) {
    //                        valueLiters = ""
    //                    }
    //                } else {
    //                    parity = 0;
    //                    valueFuelLevel = table[devTableRow]
    //                    if(valueFuelLevel == undefined) {
    //                        valueFuelLevel = ""
    //                    }

    //                    var roleLiters = "roleLiters" + devIndex
    //                    var roleFuelLevel = "roleFuelLevel" + devIndex

    //                    var itemArray = jsonArray[rowIndex]
    //                    if(itemArray === undefined) {
    //                        itemArray = {}
    //                        jsonArray.push(itemArray)
    //                    }
    //                    itemArray[roleLiters] = valueLiters;
    //                    itemArray[roleFuelLevel] = valueFuelLevel;
    //                    jsonArray[rowIndex] = itemArray
    //                    rowIndex ++
    //                }
    //            }
    //        }
    //        for(var len=0; len<jsonArray.length; len++) {
    //            if(tarTabViewMultiple.model.get(len) === undefined) {
    //                tarTabViewMultiple.currentRow = 0
    //                tarTabViewMultiple.model.append(jsonArray[len])
    //            } else {
    //                tarTabViewMultiple.model.set(len, jsonArray[len])
    //            }
    //        }
    //        timerAffterRefrashTarTable.start()
    //    }

    //    function changeDeviceUniqId() {
    //        changeDevId.open()
    //    }

    //    Timer {
    //        id: timerTestRepeat
    //        interval: 1000
    //        running: true
    //        repeat: true
    //        onTriggered: {
    //            var devCount = viewController.getStayedDevTarrirCount()
    //            var devId = viewController.getStayedDevTarrir_DevProperty("id")
    //            var colorArray = []
    //            colorArray.push("#f34b4b")
    //            colorArray.push("#4bd5f3")
    //            colorArray.push("#f34be1")
    //            colorArray.push("#4bf3c6")
    //            colorArray.push("#4b4bf3")
    //            colorArray.push("#be4bf3")
    //            colorArray.push("#0d8741")
    //            chartTarCurrentValuesMultiple.removeAllSeries();

    //            for(var devIter=0; devIter<devCount; devIter++) {
    //                var res = viewController.getTarCurrentDeviceData(devIter)
    //                var dataArray = tarListDevice.model.get(devIter)
    //                if(dataArray !== undefined) {
    //                    dataArray["valueCnt"] = res[0]
    //                    dataArray["valueFuelLevel"] = res[2]
    //                    tarListDevice.model.set(devIter, dataArray)
    //                }
    //                //-- chart
    //                var chartArray = viewController.getTarCurrentDeviceChartData(devIter)

    //                var line = chartTarCurrentValuesMultiple.createSeries(ChartView.SeriesTypeLine, "ID" + devId[devIter], currentTarChartAxisXMultiple, currentTarChartAxisYMultiple);
    //                line.color = colorArray[devIter]

    //                chartTarCurrentValuesMultiple.graphLength = chartArray.length
    //                chartTarCurrentValuesMultiple.graphAmplitudeMax = 0

    //                for(var chartIter=0; chartIter<chartArray.length; chartIter++) {
    //                    if(chartTarCurrentValuesMultiple.graphAmplitudeMax < chartArray[chartIter]) {
    //                        chartTarCurrentValuesMultiple.graphAmplitudeMax = chartArray[chartIter];
    //                    }
    //                }

    //                currentTarChartAxisXMultiple.min = 0;
    //                currentTarChartAxisXMultiple.max = chartArray.length
    //                currentTarChartAxisYMultiple.min = 0;
    //                currentTarChartAxisYMultiple.max = chartTarCurrentValuesMultiple.graphAmplitudeMax

    //                for(chartIter=0; chartIter<chartArray.length; chartIter++) {
    //                    line.append(chartIter, parseInt(chartArray[chartIter]));
    //                }
    //            }
    //        }
    //    }
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
                                        id: levelValueLabel
                                        text: qsTr("Напряжение:")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }
                                    RadialBar {
                                        id: levelProgress
                                        anchors.top: levelValueLabel.bottom
                                        anchors.topMargin: 15
                                        anchors.left: parent.left
                                        anchors.leftMargin: 20
                                        width: 150
                                        height: 150
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
                                            pointSize: 16
                                        }
                                        suffixText: "%"
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
                                        id: levelCnt
                                        anchors.top: levelCntLabel.bottom
                                        anchors.topMargin: 15
                                        anchors.left: parent.left
                                        anchors.leftMargin: 20
                                        width: 150
                                        height: 150
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
                                            pointSize: 16
                                        }
                                        suffixText: ""
                                        textColor: "#888d91"
                                        enabled: devProperty.isReady
                                        //                                        onValueChanged: {
                                        //                                            levelCntValueCustom.text = value
                                        //                                        }
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
                                    id: rectangle1
                                    width: 200
                                    height: 150
                                    layer.enabled: true
                                    radius: 15
                                    Label {
                                        id: levelTempLabel
                                        text: qsTr("Карта")
                                        anchors.left: parent.left
                                        color: "#888d91"
                                        anchors.leftMargin: 15
                                        anchors.right: parent.right
                                        anchors.rightMargin: 0
                                    }

                                    TextField {
                                        id: textField
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

                                    ProgressBar {
                                        id: progressBar
                                        x: 17
                                        y: 41
                                        to: 100
                                        anchors.left: parent.left
                                        anchors.leftMargin: 5
                                        anchors.right: parent.right
                                        anchors.rightMargin: 5
                                        value: 0
                                    }

                                    ProgressBar {
                                        id: progressBar1
                                        x: 7
                                        y: 72
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        anchors.leftMargin: 5
                                        anchors.rightMargin: 5
                                        to: 100
                                        value: 0
                                    }

                                    ProgressBar {
                                        id: progressBar2
                                        x: 11
                                        y: 104
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        anchors.leftMargin: 5
                                        anchors.rightMargin: 5
                                        to: 100
                                        value: 0
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
                                    title: "Уровень/Объем"
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

                TextArea {
                    id: log
                    text: qsTr("")
                    placeholderText: "Сообщения"
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    anchors.fill: parent
                }
            }

            Item {
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
                                            anchors.leftMargin: 0
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 10
                                            anchors.top: parent.top
                                            anchors.topMargin: 30
                                            TextField {
                                                id: accelCoefX
                                                height: 30
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                width: 300
                                                placeholderText: "введите значение"
                                            }
                                            TextField {
                                                id: accelCoefY
                                                height: 30
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                width: 300
                                                placeholderText: "введите значение"
                                            }
                                            TextField {
                                                id: accelCoefZ
                                                height: 30
                                                anchors.left: parent.left
                                                anchors.leftMargin: 15
                                                width: 300
                                                placeholderText: "введите значение"
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
                                    }
                                }
                            }
                        }
                    }

                    Item {
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
                                                //                                                    id: accelCoefX
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

    //    Rectangle {
    //        id: busyIndicator
    //        width: 350
    //        height: 200
    //        radius: 20
    //        visible: false
    //        property string message: "Ожидание ответа..."
    //        anchors.horizontalCenter: parent.horizontalCenter
    //        anchors.verticalCenter: parent.verticalCenter
    //        BusyIndicator {
    //            id: waitReadyIndicator
    //            width: 96
    //            height: 96
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            anchors.verticalCenter: parent.verticalCenter
    //        }
    //        Label {
    //            text: busyIndicator.message
    //            anchors.top: waitReadyIndicator.bottom
    //            anchors.topMargin: 20
    //            anchors.horizontalCenter: parent.horizontalCenter
    //        }
    //        layer.enabled: true
    //        layer.effect: DropShadow {
    //            transparentBorder: true
    //            horizontalOffset: 0
    //            verticalOffset: 1
    //            color: "#e0e5ef"
    //            samples: 10
    //            radius: 10
    //        }
    //    }

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
        //        onApply: {
        //            close()
        //        }
    }

    //    Timer {
    //        id: timerAffterRefrashTarTable
    //        interval: 100
    //        running: false
    //        repeat: false
    //        onTriggered: {
    //            remakeTarTableChart()
    //        }
    //    }
}
