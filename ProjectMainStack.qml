import QtQuick 2.9
import QtQuick.Controls 2.4

Component {
    id:projectMainStack
    Rectangle {
        id: projectMainLayout
        color: "#ffffff"



        Rectangle {
            id: currentStateRectangle
            width: 300
            color: "#fdfdfd"
            radius: 0
            border.width: 1
            border.color: "#9899a7"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            StackView {
                id: deviceTabParameters
                initialItem: parametersRectangle
                anchors.bottomMargin: 0
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
            color: "#fdfdfd"
            border.color: "#81a8b9"
            anchors.right: currentStateRectangle.left
            anchors.rightMargin: 10
            anchors.left: currentStateRectangle.left
            anchors.leftMargin: -projectMainLayout.width + currentStateRectangle.width + 20
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
