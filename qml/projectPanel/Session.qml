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

    function loadSessionTree() {
        var sessionList = viewController.getListSession()
        openSessionListView.model.clear()
        for(var i=0; i<sessionList.length; i++) {
            openSessionListView.model.append({"sessionName":sessionList[i]})
        }
    }

    onOpened: {
        loadSessionTree()
    }

    Row {
        spacing: 25
        height: parent.height

        Rectangle {
            id:rootRectangle
            width: parent.width/2 + 50
            height: parent.height
            color: "#f7f7f7"
            SwipeView {
                id:panelSwipe
                currentIndex: sessionSelectMode
                anchors.fill: parent
                interactive: false
                clip: true
                Item {
                    Column {
                        ListView {
                            id: openSessionListView
                            width: rootRectangle.width
                            height: rootRectangle.height
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
                                        width: 250
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
                                        id:removeButton
                                        text: "\uf1f8"
                                        width: 50
                                        height: 25
                                        anchors.top: parent.top
                                        anchors.topMargin: 5
                                        anchors.left: loadSessionName.right
                                        anchors.leftMargin: 5
                                        onClicked: {
                                            var list = openSessionListView.model.get(index)
                                            var res = list["sessionName"]
                                            if(res !== undefined) {
                                                if(viewController.removeSessionByName(res)) {
                                                    loadSessionTree()
                                                }
                                            }
                                        }
                                    }
                                    Button {
                                        id:loadButton
                                        text: "Загрузить"
                                        width: 100
                                        height: 25
                                        anchors.top: parent.top
                                        anchors.topMargin: 5
                                        anchors.left: removeButton.right
                                        anchors.leftMargin: 5
                                        onClicked: {
                                            var list = openSessionListView.model.get(index)
                                            viewController.resetSession()
                                            viewController.loadSession(list["sessionName"])
                                            close()
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
                        anchors.centerIn: parent
                        height: 100
                        width: parent.width
                        TextField {
                            id:saveSessionSimpleName
                            width: parent.width
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
                                        sessionSelectMode = 0
                                        loadSessionTree()
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
            width: 300
            MiscElems.ButtonRound {
                id:openSimple
                textLine: 1
                widthBody: 150
                name:"Открыть"
                iconCode: "\uf12a  "
                useIcon: true
                onClicked: {
                    sessionSelectMode = 0
                }
            }
            Column {
                spacing: 10
                MiscElems.ButtonRound {
                    id:saveSimple
                    textLine: 1
                    widthBody: 150
                    name:"Сохранить"
                    iconCode: "\uf4d3  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 1
                        var res = viewController.saveCurrentSession()
                        if(res.length !==0) {
                            saveSessionSimpleName.text = res
                            var timer = Qt.createQmlObject('import QtQuick 2.4;Timer{interval: 1200;running:true;repeat: false;}', parent);
                            timer.onTriggered.connect(function() {
                                saveSessionSimpleName.text = ""
                                sessionSelectMode = 0
                                loadSessionTree()
                            });
                        }
                    }
                }
                MiscElems.ButtonRound {
                    id:saveAs
                    textLine: 1
                    widthBody: 150
                    name:"Сохранить как"
                    iconCode: "\uf0c7  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 2
                    }
                }
                MiscElems.ButtonRound {
                    id:closeButton
                    textLine: 1
                    widthBody: 150
                    name:"Закрыть"
                    iconCode: "\uf410  "
                    useIcon: true
                    onClicked: {
                        sessionSelectMode = 2
                        close()
                    }
                }
            }
        }
    }
}
