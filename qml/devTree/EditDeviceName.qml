import QtQuick 2.4
import Qt.labs.platform 1.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "qrc:/qml/miscElems"

Popup {
    id: popup
    width: 500
    height: 120
    x: width / 2
    y: height / 2
    modal: true

    signal acceptConnectReady(var name, var baudrate)
    signal abortConnectButton()

    property string lastDevName: ""

    function setDeviceName(devName) {
        devHeaderText.text = devName
        lastDevName = devName
    }

    Column {
        spacing: 10
        Row {
            spacing: 10
            TextField {
                id:devHeaderText
                width: 300
                height: 30
                placeholderText: "Имя устройства"
                onFocusChanged: {
                    if(text.length === 0) {
                        text = lastDevName
                    }
                }
            }
            ButtonRound {
                id: buttonAccept
                textLine: 1
                widthBody: 140
                textIsCenter: true
                name: qsTr("Изменить")
                useIcon: true
                iconCode: "\uf13a  "
                onClicked: {
                    if(devHeaderText.length !== 0) {
                        var key = []
                        var value = []
                        key.push("newHeader")
                        value.push(devHeaderText.text)
                        viewController.setCurrentDevCustomCommand("change device head name", key, value)
                        close()
                    }
                }
            }
        }
        ButtonRound {
            id: buttonClose
            textLine: 1
            anchors.right: parent.right
            widthBody: 140
            textIsCenter: true
            useIcon: true
            iconCode: "\uf00d  "
            name: qsTr("Закрыть")
            onClicked: {
                close()
            }
        }
    }
}
