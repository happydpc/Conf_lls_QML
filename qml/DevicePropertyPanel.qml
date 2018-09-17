import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11

Rectangle {
    id: projectDevicePanel

    property DevPropertyProgressTmk24 devPropertyProgressTmk24: devPropertyProgressTmk24

    function setActivePanelType(typeDev) {
        console.log("setActivePanelType -" + typeDev)
        switch(typeDev) {
        case "SerialPort":
            devicePropertieslistModel1.currentIndex = 1
            break;
        case "Empty":
            devicePropertieslistModel1.currentIndex = 0
            break;
        case "PROGRESS TMK24":
            devicePropertieslistModel1.currentIndex = 2
            devPropertyProgressTmk24.setResetState()
            break;
        default:
            console.log("setActivePanelType -unrecognise type dev")
            break;
        }
    }
    property alias dialogAddDeviceFail : dialogAddDeviceFail
    property alias dialogAddInterfaceFail: dialogAddInterfaceFail
    property alias messageOperationError: messageOperationError

    function setPropertyToSerialPort(listData) {
        devPropertySerialPort.setPropertyValues(listData)
    }
    function devShowPasswordIncorrect(devType, devNameId) {
        dialogPasswordError.messageArg = devNameId
        dialogPasswordError.open()
        switch(devType) {
        case "PROGRESS TMK24":
            devicePropertieslistModel1.currentIndex = 2
            devPropertyProgressTmk24.setWriteSettingsIsNoAvailable()
            break;
        default:
            console.log("devShowPasswordIncorrect -unrecognise type dev")
            break;
        }
    }
    function devShowTypeIncorrect(devNameId) {
        dialogTypeError.messageArg = devNameId
        dialogTypeError.open()
    }

    Rectangle {
        id: parametersRect
        color: "transparent"
        anchors.fill: parent
        anchors.top: parent.top

        StackView {
            id: portOrDeviceStack
            anchors.fill: parent

            Rectangle {
                id: currentStateRectangle
                color: "transparent"
                anchors.fill: parent
                border.width: 1
                border.color: "#9899a7"

                SwipeView {
                    id: devicePropertieslistModel1
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 1
                    anchors.rightMargin: 1
                    interactive: false
                    clip: true

                    Item {
                        Rectangle {
                            id: logoSubPanel
                            anchors.fill: parent
                            height: 500
                            width: 500
                            color: "red"
                            LogoPanel {

                            }
                        }
                    }
                    Item {
                        DevPropertySerialPort {
                            id: devPropertySerialPort
                        }
                    }
                    Item{
                        DevPropertyProgressTmk24 {
                            id: devPropertyProgressTmk24
                        }
                    }
                }
            }
        }

        Dialog {
            id: dialogAddDeviceFail
            visible: false
            title: "Добавление устройства"
            standardButtons: StandardButton.Close
            Rectangle {
                color: "transparent"
                implicitWidth: 250
                implicitHeight: 100
                Text {
                    text: "Не получилось добавить устройство\nТакой адрес уже используется"
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

        Dialog {
            id: dialogAddInterfaceFail
            visible: false
            title: "Добавление интерфейса"
            standardButtons: StandardButton.Close
            Rectangle {
                color: "transparent"
                implicitWidth: 350
                implicitHeight: 100
                Text {
                    text: "Не получилось добавить интерфейс\nВозможно такой интерфейс уже используется\nили ресурс не доступен"
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

        Dialog {
            id: dialogPasswordError
            visible: false
            title: "Ошибка пароля"
            standardButtons: StandardButton.Apply
            property string messageArg: ""
            width: 500
            height: 150
            Rectangle {
                color: "transparent"
                anchors.fill: parent
                Text {
                    text: qsTr("Настроечный пароль устройства %1 не совпадает\nс установленным в устройстве\nЗапись настроек не возможна!").arg(dialogPasswordError.messageArg)
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
            onApply: {
                close()
            }
        }

        Dialog {
            id: dialogTypeError
            visible: false
            title: "Ошибка типа устройства"
            standardButtons: StandardButton.Apply
            property string messageArg: ""
            width: 500
            height: 150
            Rectangle {
                color: "transparent"
                anchors.fill: parent
                Text {
                    text: qsTr("Тип устройства не совпадает с заявленным при создании [%1]\nЭто устройство удалено из списка!").arg(dialogTypeError.messageArg)
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
            onApply: {
                close()
            }
        }

        Dialog {
            id: messageOperationError
            visible: false
            title: "Ошибка операции"
            standardButtons: StandardButton.Close
            property string message: ""
            Rectangle {
                color: "transparent"
                implicitWidth: 450
                implicitHeight: 100
                Text {
                    text: messageOperationError.message
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

    }
}
