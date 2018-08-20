import QtQuick 2.4
import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import Qt.labs.calendar 1.0

import Qt.labs.platform 1.0

Item {
    width: 1100
    height: 800
    property alias statusBar: statusBar

    Rectangle {
        id: vewRootForm
        color: "#ffffff"
        anchors.fill: parent

        Rectangle {
            id: statusBarRecangle
            height: 30
            color: "#0029bb"
            radius: 0
            border.width: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Label {
                id: statusBar
                color: "#ffffff"
                text: qsTr("Label")
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: projectRecangle
            color: "#ffffff"
            anchors.bottom: statusBarRecangle.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottomMargin: 0

            BattleList {
                id: stackView
                anchors.fill: parent
            }

            Rectangle {
                id: currentStateRectangle
                width: 300
                color: "#fdfdfd"
                radius: 0
                border.width: 1
                border.color: "#9899a7"
                anchors.bottom: stackView.bottom
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10

                StackView {
                    id: stackView1
                    anchors.fill: parent

                    TabBar {
                        id: tabBar
                        anchors.left: parent.left
                        anchors.leftMargin: 1
                        anchors.right: parent.right
                        anchors.rightMargin: 1
                        anchors.top: parent.top
                        anchors.topMargin: 1

                        TabButton {
                            id: currentData
                            text: qsTr("Текущие данные")
                            focusPolicy: Qt.TabFocus
                        }

                        TabButton {
                            id: slaves
                            text: qsTr("Ведомые")
                        }

                        TabButton {
                            id: log
                            text: qsTr("Журнал")
                        }
                    }
                }
            }

            Rectangle {
                id: parametersRectangle
                color: "#ffffff"
                border.color: "#81a8b9"
                anchors.right: currentStateRectangle.right
                anchors.rightMargin: currentStateRectangle.width + 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: currentStateRectangle.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 10
            }
        }
    }
}
