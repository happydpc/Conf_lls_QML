import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.10
import Qt.labs.platform 1.0
import QtCharts 2.2
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4

Rectangle {
    id: rectangle2
    color: "#e7e9eb"
    width: 600
    height: 500

    Rectangle {
        id: rectangle
        clip: true
        anchors.fill: parent

        StackView {
            id: exerciseView
            anchors.top: topBar.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: exercise.right
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            initialItem: statsItem
        }

        Rectangle {
            id: topBar
            y: 0
            height: 60
            color: "#ffffff"
            anchors.left: parent.left
            anchors.leftMargin: 121
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            ToolButton {
                id: toolButton
                x: 431
                text: qsTr("...")
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
            }

            Label {
                id: status
                x: 135
                y: 36
                text: qsTr("...")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: exercise
            x: 10
            y: 10
            width: 114
            color: "#ffffff"
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            Column {
                anchors.fill: parent
                spacing: 2

                Button {
                    id: exerciseAdition
                    text: "Adition"
                }
                Button {
                    id: exerciseDivision
                    text: "Division"
                }
                Button {
                    id: exerciseExponention
                    text: "Exponention"
                }
                Button {
                    id: exerciseMultiplication
                    text: "Multiplication"
                }
                Button {
                    id: exerciseRoot
                    text: "Root"
                }
                Button {
                    id: exerciseSubstraction
                    text: "Substraction"
                }
            }
        }
    }

    Item {
        id: statsItem
        visible: false
        anchors.fill: parent

        Row {
            id: row
            y: 357
            height: 50
            spacing: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15

            ChartView {
                id: chart
                height: parent.height - 300
                width: parent.width + 100
                anchors.left: parent.left
                anchors.leftMargin: -20
                anchors.right: parent.right
                anchors.rightMargin: -20
                theme: ChartView.ChartThemeLight
                title: "Value/Level"
                antialiasing: true
                visible: devPropertyProgressTmk4ux.isReady
                property int chartLength: 1
                property int chartAmplitudeMax: 1
                ValueAxis {
                    id: axisX
                    min: 0
                    max: graph.graphLength
                    tickCount: 5
                }
                ValueAxis {
                    id: axisY
                    min: 0
                    max: graph.graphAmplitudeMax
                    tickCount: 5
                }
                LineSeries {
                    id: series1
                    axisX: axisX
                    axisY: axisY
                }
            }

            Button {
                id: statsButtonWeek
                text: qsTr("week")
            }

            Button {
                id: statsButtonMonth
                text: qsTr("month")
            }

            Button {
                id: statsButtonAllTime
                text: qsTr("all time")
            }
        }
    }
}

/*##^## Designer {
    D{i:31;anchors_height:200;anchors_width:200;anchors_x:259;anchors_y:57}D{i:34;anchors_y:12}
D{i:35;anchors_x:135;anchors_y:36}D{i:32;anchors_width:418;anchors_x:133;anchors_y:39}
D{i:24;anchors_height:456;anchors_width:118;anchors_x:10;anchors_y:10}D{i:33;anchors_height:200;anchors_width:200}
}
 ##^##*/
