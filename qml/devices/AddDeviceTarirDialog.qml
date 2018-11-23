import QtQuick 2.4
import QtQuick.Controls 2.3
//import QtQuick.Layouts 1.1
//import QtGraphicalEffects 1.0

import "qrc:/qml/miscElems" as MiscElems

Popup {
    id: addDeviceTarirDialog

    signal accepted(var deviceTypeName, var deviceId, var deviceSerialNumber)

    width: 830
    height: 600
    modal: true
    clip: true

    Rectangle {
        id:rootRectangle
        anchors.fill: parent

        MiscElems.ButtonRound {
            id:buttonAddChecked
            textLine: 2
            widthBody: 240
            anchors.top: tarirDevicesRectangle.bottom
            anchors.right: parent.right
            anchors.topMargin: 10
            textIsCenter: true
            name: qsTr("Принять")
            useIcon: true
            iconCode: "\uf00c  "
            onClicked: {
                var size = tarDevListView.count
                var deviceTypeName = []
                var deviceId = []
                var deviceSerialNumber = []
                for(var i=0; i<size; i++) {
                    var item = tarDevListView.model.get(i)
                    deviceTypeName.push(item.deviceTypeName)
                    deviceId.push(item.deviceId)
                    deviceSerialNumber.push(item.deviceSerialNumber)
                }
                accepted(deviceTypeName, deviceId, deviceSerialNumber)
                close()
            }
        }
        MiscElems.ButtonRound {
            id:buttonExit
            textLine: 2
            widthBody: 200
            anchors.top: tarirDevicesRectangle.bottom
            anchors.right: buttonAddChecked.left
            anchors.topMargin: 10
            anchors.rightMargin: 10
            textIsCenter: true
            useIcon: true
            iconCode: "\uf00d  "
            name: qsTr("Закрыть")
            onClicked:  {
                close()
            }
        }
        Rectangle {
            id:tarirDevicesRectangle
            color: "#f6f6f6"
            radius: 15
            width: 400
            height: parent.height - buttonAddChecked.height - 5
            Label {
                id:tarrirDevicesheader
                text: "Тарируемые устройства:"
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            ListView {
                id: tarDevListView
                anchors.top: tarrirDevicesheader.bottom
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 400
                clip: true

                ScrollBar.vertical: ScrollBar {
                    width: 20
                }
                delegate: Item {
                    id: tarDevListViewDelegate
                    height: 100
                    width: parent.width

                    Rectangle {
                        width: parent.width
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        height: parent.height
                        color: "transparent"
                        TextField {
                            id: deviceTypeName
                            height: 25
                            width: 250
                            text: model.deviceTypeName
                            font.bold: false
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#ded3d3"
                            }
                        }
                        TextField {
                            id: deviceId
                            height: 25
                            width: 250
                            text: model.deviceId
                            font.bold: false
                            anchors.top: deviceTypeName.bottom
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#c4e7c3"
                            }
                        }
                        TextField {
                            id: deviceSerialNumber
                            height: 25
                            width: 250
                            text: model.deviceSerialNumber
                            font.bold: false
                            anchors.top: deviceId.bottom
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#e7e1c0"
                            }
                        }
                        Button {
                            text: "Убрать"
                            width: 100
                            height: 30
                            anchors.top: parent.top
                            anchors.topMargin: 15
                            anchors.left: deviceSerialNumber.right
                            anchors.leftMargin: 5
                            onClicked: {
                                var tarList = tarDevListView.model.get(index)
                                availableDevListView.model.append(tarList)
                                tarDevListView.model.remove(index)
                            }
                        }
                    }
                }
                model: ListModel {
                    id: tarDevListModel
                }
            }
        }

        Rectangle {
            id:availableDevicesRectangle
            anchors.leftMargin: 10
            anchors.left: tarirDevicesRectangle.right
            height: parent.height - buttonAddChecked.height - 5
            color: "#f6f6f6"
            radius: 15
            width: 400
            Label {
                id:availablerDevicesheader
                text: "Доступные устройства для добавления:"
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            ListView {
                id: availableDevListView
                anchors.top: availablerDevicesheader.bottom
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 400
                clip: true

                ScrollBar.vertical: ScrollBar {
                    width: 20
                }
                delegate: Item {
                    id: availableDevListViewDelegate
                    height: 100
                    width: parent.width

                    Rectangle {
                        width: parent.width
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        height: parent.height
                        color: "transparent"
                        TextField {
                            id: availableDeviceTypeName
                            height: 25
                            width: 250
                            text: model.deviceTypeName
                            font.bold: false
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#ded3d3"
                            }
                        }
                        TextField {
                            id: availableDeviceId
                            height: 25
                            width: 250
                            text: model.deviceId
                            font.bold: false
                            anchors.top: availableDeviceTypeName.bottom
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#c4e7c3"
                            }
                        }
                        TextField {
                            id: availableDeviceSerialNumber
                            height: 25
                            width: 250
                            text: model.deviceSerialNumber
                            font.bold: false
                            anchors.top: availableDeviceId.bottom
                            anchors.left: parent.left
                            readOnly: true
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#e7e1c0"
                            }
                        }
                        Button {
                            text: "Добавить"
                            width: 100
                            height: 30
                            anchors.top: parent.top
                            anchors.topMargin: 15
                            anchors.left: availableDeviceSerialNumber.right
                            anchors.leftMargin: 5
                            onClicked: {
                                var availableList = availableDevListView.model.get(index)
                                tarDevListView.model.append(availableList)
                                availableDevListView.model.remove(index)
                            }
                        }
                    }
                }
                model: ListModel {
                    id: availableDevListModel
                }
            }
        }
    }
    onOpened: {
        tarDevListView.model.clear()
        availableDevListView.model.clear()
        var connDevType = controller.getAvailableDevTarrirAdd_DevType()
        var connDevId = controller.getAvailableDevTarrirAdd_DevId()
        var connDevSn = controller.getAvailableDevTarrirAdd_DevSerialNumber()
        var tarirDevType = controller.getStayedDevTarrir_DevProperty("type")
        var tarirDevId =  controller.getStayedDevTarrir_DevProperty("id")
        var tarirDevSn = controller.getStayedDevTarrir_DevProperty("sn")
        // available list
        for(var i=0; i<connDevType.length; i++) {
            var isCopy = false
            for(var found=0; found<tarirDevId.length; found++) {
                if(parseInt(connDevId[i]) == parseInt(tarirDevId[found])) {
                    isCopy = true
                }
            }
            if(!isCopy) {
                availableDevListView.model.append({"deviceTypeName":connDevType[i],"deviceId":connDevId[i], "deviceSerialNumber":connDevSn[i]})
            }
        }
        // currnet dev tatir
        for(i=0; i<tarirDevType.length; i++) {
            tarDevListView.model.append({"deviceTypeName":tarirDevType[i],"deviceId":tarirDevId[i], "deviceSerialNumber":tarirDevSn[i]})
        }
    }
}
