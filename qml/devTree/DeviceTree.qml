import QtQuick 2.4
import QtQuick.Dialogs 1.2

Column{
    spacing: 20
    Repeater{
        model: modelData.childItems
        delegate: Row {
            id: deviceTreeView
            Rectangle {
                id:rectBase
                width: 210
                height: 20
                MouseArea {
                    id:area
                    anchors.left: iconDelete.right
                    anchors.rightMargin: 5
                    acceptedButtons: Qt.LeftButton
                    width: 125
                    height: 50
                    onClicked: {
                        modelData.isCurrent = true
                    }
                    Column {
                        id:deviceIdentColumn
                        TextInput {
                            id:deviceName
                            width: 125
                            readOnly: true
                            color: modelData.isCurrent === true ? "#46e342" : "#3598fa"
                            text: modelData.content
                            clip: true
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    modelData.isCurrent = true
                                }
                            }
                        }
                        TextInput {
                            id:deviceHeader
                            width: 125
                            readOnly: true
                            color: modelData.isCurrent === true ? "#46e342" : "#3598fa"
                            text: modelData.header
                            clip: true
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    modelData.isCurrent = true
                                }
                            }
                        }
                    }
                }
                Text {
                    id:iconEditDeviceHeader
                    text: " \uf1fb"
                    color: modelData.isConnected === true ? ("#58fce4") : (iconEditMouse.isFocused === true ? "#58fce4" : "#dbd9d9")
                    font { family: "customFont";}
                    font.pointSize: 14
                    anchors.left: parent.left
                    width: 28
                    height: 28
                    MouseArea {
                        id:iconEditMouse
                        acceptedButtons: Qt.LeftButton
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool isFocused: false
                        onEntered: {
                            isFocused = true
                        }
                        onExited: {
                            isFocused = false
                        }
                        onClicked: {
                            modelData.isCurrent = true
                            var keys = viewController.getCurrentDevPropertyKey()
                            var values = viewController.getCurrentDevPropertyValue()
                            for(var i=0; i<keys.length; i++) {
                                if(keys[i] === "header"){
                                    editDeviceName.setDeviceName(values[i])
                                    editDeviceName.open()
                                }
                            }
                        }
                    }
                }
                Text {
                    id:iconDelete
                    text: " \uf1f8"
                    color: iconDeleteMouse.isFocused === true ? "#58fce4" : "#dbd9d9"
                    font { family: "customFont";}
                    font.pointSize: 14
                    anchors.left: iconEditDeviceHeader.right
                    width: 28
                    height: 28
                    MouseArea {
                        id:iconDeleteMouse
                        acceptedButtons: Qt.LeftButton
                        hoverEnabled: true
                        anchors.fill: parent
                        property bool isFocused: false
                        onEntered: {
                            isFocused = true
                        }
                        onExited: {
                            isFocused = false
                        }
                        onClicked: {
                            console.log("MouseArea deviceTree clicked")
                            modelData.isCurrent = true
                            if (mouse.button === Qt.LeftButton) {
                                removeDeviceDialog.open()
                            }
                        }
                    }
                }
            }
            Column{
                id:column
                spacing: 20
            }
        }
    }

    EditDeviceName {
        id:editDeviceName
    }

    Dialog {
        id:removeDeviceDialog
        visible: false
        title: "Удалить устройство"
        standardButtons: StandardButton.Close | StandardButton.Apply
        Rectangle {
            color: "transparent"
            implicitWidth: 250
            implicitHeight: 100
            Text {
                text: "Вы хотите удалить устройство?"
                color: "black"
                anchors.centerIn: parent
            }
        }
        onApply: {
            viewController.removeActiveDevice()
            close()
        }
    }

    FontLoader { id: customFont; source: "qrc:/font/fonts/awesome_900.ttf" }
}
