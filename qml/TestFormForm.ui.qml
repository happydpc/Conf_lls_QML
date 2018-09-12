import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4 as ControlOld

Rectangle {
    id: cnangeId
    color: "#e7e9eb"
    width: 350
    height: 350

    Column {
        id: column
        spacing: 10
        anchors.fill: parent

        Label {
            text: qsTr("Поиск устройств:")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ControlOld.TableView {
            id: searchDeviceView
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10

            ControlOld.TableViewColumn {
                id: tableDelegateValue
                role: "id"
                title: "Тип"
                property int value: model.Value
                delegate: Rectangle {
                    anchors.fill: parent
                    color: valueInputValue.text.length > 0 ? "transparent" : "red"
                    TextInput {
                        id: valueInputValue
                        anchors.fill: parent
                        selectionColor: "red"
                        text: (model.Value === 0) ? "0" : model.Value
                        validator: RegExpValidator {
                            regExp: /[0-9A-F]+/
                        }
                        //                        onEditingFinished: {
                        //                            model.Value = text
                        //                            remakeTarTableChart()
                        //                        }
                    }
                }
            }
            model: ListModel {
                id: searchDeviceViewModel
            }
            //            onCurrentRowChanged: {
            //                tarTabView.selection.clear()
            //                tarTabView.selection.select(tarTabView.currentRow)
            //            }
            rowDelegate: Rectangle {
                SystemPalette {
                    id: systemPalette
                    colorGroup: SystemPalette.Active
                }
                //                color: {
                //                    var baseColor = styleData.alternate ? systemPalette.alternateBase : systemPalette.base
                //                    return styleData.selected ? "orange" : baseColor
                //                }
            }
        }

        Button {
            id: accept
            text: qsTr("Снять выделение")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
        Button {
            id: exit
            text: qsTr("Добавиь выделенные")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            height: 50
        }
    }
}
