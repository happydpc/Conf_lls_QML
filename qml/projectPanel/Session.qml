import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

import "qrc:/qml/miscElems" as MiscElems

Popup {
    modal: true
    width: 700
    height: 250
    clip: true

    property int sessionSelectMode: 0

    onOpened: {
        var sessionList = viewController.getListSession()
        for(var i=0; i<sessionList.length; i++) {
            openSessionListView.model.append({"sessionName":sessionList[i]})
        }
    }

    Row {
        spacing: 25
        height: parent.height

        Rectangle {
            width: parent.width/2
            height: parent.height
            color: "#ffffff"
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 1
                color: "#e0e5ef"
                samples: 10
                radius: 10
            }
            SwipeView {
                id:panelSwipe
                currentIndex: sessionSelectMode
                anchors.fill: parent
                clip: true
                Item {
                    Column {
                        anchors.fill: parent
                        ListView {
                            id: openSessionListView
                            anchors.fill: parent
                            clip: true
                            ScrollBar.vertical: ScrollBar {
                                width: 20
                            }
                            delegate: Item {
                                height: 50
                                width: parent.width

                                Rectangle {
                                    width: parent.width
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.rightMargin: 10
                                    height: parent.height
                                    color: "transparent"
                                    TextField {
                                        id: loadSessionName
                                        height: 25
                                        width: 200
                                        text: model.sessionName
                                        font.bold: false
                                        anchors.top: parent.top
                                        anchors.topMargin: 5
                                        anchors.left: parent.left
                                        readOnly: true
                                        background: Rectangle {
                                            anchors.bottom: parent.bottom
                                            height: 2
                                            color: "#7487b4"
                                        }
                                    }
                                    Button {
                                        text: "Загрузить"
                                        width: 100
                                        height: 25
                                        anchors.top: parent.top
                                        anchors.topMargin: 5
                                        anchors.left: loadSessionName.right
                                        anchors.leftMargin: 5
                                        onClicked: {
                                        }
                                    }
                                }
                            }
                            model: ListModel {
                                id: tarDevListModel
                            }
                        }
                    }
                }
                Item {
                    Column {
                        anchors.fill: parent
                        TextField {
                            id:saveSessionSimpleName
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            placeholderText: "Название авто сохранения"
                            readOnly: true
                        }
                    }
                }
                Item {
                    Column {
                        anchors.centerIn: parent
                        height: 100
                        width: parent.width
                        TextField {
                            id:saveSessionAsName
                            width: parent.width
                            height: 50
                            placeholderText: "Введите название сохранения"
                        }
                        Button {
                            id:saveSessionAsNameButton
                            text:"Сохранить"
                            width: parent.width
                            height: 50
                            enabled: saveSessionAsName.text.length
                            onClicked: {
                                var res = viewController.saveCurrentSessionAs(saveSessionAsName.text)
                                if(res.length !==0) {
                                    saveSessionAsName.text = res
                                    var timer = Qt.createQmlObject('import QtQuick 2.4;Timer{interval: 1500;running:true;repeat: false;}', parent);
                                    timer.onTriggered.connect(function() {
                                        saveSessionAsName.text = ""
                                    });
                                }
                            }
                        }
                    }
                }
            }
        }
        Column {
            spacing: 20
            anchors.verticalCenter: parent.verticalCenter
            Label {
                text: qsTr("Открытие")
            }
            Row {
                MiscElems.ButtonRound {
                    id:openSimple
                    textLine: 2
                    widthBody: 150
                    name:"Открыть"
                    iconCode: "\uf12a  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 0
                    }
                }
            }
            Label {
                text: qsTr("Сохранение")
            }
            Row {
                spacing: 10
                MiscElems.ButtonRound {
                    id:saveSimple
                    textLine: 2
                    widthBody: 150
                    name:"Сохранить"
                    iconCode: "\uf12a  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 1
                        saveSessionSimpleName.text = viewController.saveCurrentSession()
                    }
                }
                MiscElems.ButtonRound {
                    id:saveAs
                    textLine: 2
                    widthBody: 150
                    name:"Сохранить как"
                    iconCode: "\uf12a  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 2
                    }
                }
            }
        }
    }
}
