import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Popup {
    id: addDeviceTarirDialog

    signal accepted(var deviceTypeName, var deviceId, var deviceSerialNumber)

    width: 490
    height: 600
    modal: true
    x: parent.x / 2
    y: parent.y / 2

    Rectangle {
        id:rectangle
        anchors.fill: parent

        Label {
            id:label
            text: "Выберите устройства из списка:"
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }

        ListView {
            id: tarDevListView
            anchors.top: label.bottom
            anchors.topMargin: 10
            anchors.bottom: rectangle.bottom
            anchors.bottomMargin: 50
            anchors.left: rectangle.left
            anchors.right: rectangle.right
            clip: true

            ScrollBar.vertical: ScrollBar {
                width: 20
            }
            delegate: Item {
                id: tarDevListViewDelegate
                height: 105
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
                        width: 400
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
                        width: 400
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
                        width: 400
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
                    CheckBox {
                        width: 25
                        height: 25
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.left: deviceSerialNumber.right
                        anchors.leftMargin: 10
                        checked: model.addIsChecked
                    }
                }
            }
            model: ListModel {
                id: tarDevListModel
            }
        }
        Button {
            id:buttonAddChecked
            anchors.top: tarDevListView.bottom
            anchors.right: parent.right
            anchors.topMargin: 10
            width: 240
            height: 30
            text: "Добавить выделения"
            onClicked: {
                var size = tarDevListView.count
                var deviceTypeName = []
                var deviceId = []
                var deviceSerialNumber = []
                for(var i=0; i<size; i++) {
                    var item = tarDevListView.model.get(i)
                    if(item.addIsChecked) {
                        deviceTypeName.push(item.deviceTypeName)
                        deviceId.push(item.deviceId)
                        deviceSerialNumber.push(item.deviceSerialNumber)
                    }
                }
                accepted(deviceTypeName, deviceId, deviceSerialNumber)
                close()
            }
        }
        Button {
            id:buttonExit
            anchors.top: tarDevListView.bottom
            anchors.right: buttonAddChecked.left
            anchors.topMargin: 10
            anchors.rightMargin: 10
            width: 200
            text: "Закрыть"
            height: 30
            onClicked:  {
                close()
            }
        }
    }
    onOpened: {
        tarDevListView.model.clear()
        var listType = viewController.getAvailableDevTarrirAdd_DevType()
        var listId = viewController.getAvailableDevTarrirAdd_DevId()
        var listSn = viewController.getAvailableDevTarrirAdd_DevSerialNumber()
        for(var i=0; i<listType.length; i++) {
            tarDevListView.model.append({"deviceTypeName":listType[i],"deviceId":listId[i], "deviceSerialNumber":listSn[i], "addIsChecked":true})
        }
    }
}
