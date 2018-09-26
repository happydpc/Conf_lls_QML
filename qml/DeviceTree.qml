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
                Text {
                    id:iconRect
                    text: " \uf1fb"
                    color: modelData.isConnected === true ? "#58fce4" : "#dbd9d9"
                    font { family: "customFont";}
                    font.pointSize: 14
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

    FontLoader { id: customFont; source: "qrc:/awesome_900.ttf" }
}
