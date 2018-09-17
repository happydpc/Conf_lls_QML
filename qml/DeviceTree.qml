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
                width: 150
                height: 20

                MouseArea {
                    id:area
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    Rectangle {
                        anchors.fill: rectBase
                        color: "orange"
                    }
                    anchors.fill: parent
                    onClicked: {
                        console.log("MouseArea deviceTree clicked")
                        modelData.isCurrent = true
                        if (mouse.button === Qt.RightButton) {
                            removeDeviceDialog.open()
                        }
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
                }

                Rectangle {
                    id:iconRect
                    anchors.left: rectBase.left
                    anchors.leftMargin: 20
                    width: 16
                    height: 16
                    color: modelData.isConnected === true ? "#58fce4" : "#dbd9d9"
                }
                Text {
                    anchors.left: iconRect.right
                    anchors.leftMargin: 20
                    color: modelData.isCurrent === true ? "#46e342" : "#3598fa"
                    text: modelData.content
                }
            }
            Column{
                id:column
                spacing: 20
            }
        }
    }
}
