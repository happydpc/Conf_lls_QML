import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 1100
    height: 700
    title: qsTr("Tabs")

    View {
        id: view
        height: parent.height
        width: parent.width
    }

//    TabBar {
//        id: propertiesTabBar
//        anchors.leftMargin: 10
//        anchors.rightMargin: 10
//        anchors.top: row5.bottom
//        anchors.right: tabBar.left
//        anchors.left: parent.left
//        anchors.topMargin: 20

//        currentIndex: propertiesView.currentIndex

//        TabButton {
//            id: basePropertiesTab
//            text: qsTr("Общие параметры")
//            focusPolicy: Qt.TabFocus
//            background: Rectangle {
//                gradient: Gradient {
//                    GradientStop {
//                        position: 1
//                        color: "#4D75E0"
//                    }
//                    GradientStop {
//                        position: 0
//                        color: "#EEF0F6"
//                    }
//                }
//            }
//            onClicked: {
//                propertiesView.setCurrentIndex(1)
//            }
//        }

//        TabButton {
//            id: tempCompensationTab
//            text: qsTr("Температурная компенсация")
//            background: Rectangle {
//                gradient: Gradient {
//                    GradientStop {
//                        position: 1
//                        color: "#4D75E0"
//                    }
//                    GradientStop {
//                        position: 0
//                        color: "#EEF0F6"
//                    }
//                }
//            }
//            onClicked: {
//                propertiesView.setCurrentIndex(0)
//            }
//        }
//    }

////    Button {
////        text: qsTr("Home")
////        onClicked: swipeView.setCurrentIndex(0)
////        enabled: swipeView.currentIndex != 0
////    }

////    Button {
////        text: qsTr("Previous")
////        onClicked: swipeView.decrementCurrentIndex()
////        enabled: swipeView.currentIndex > 0
////    }

////    Button {
////        text: qsTr("Next")
////        onClicked: swipeView.incrementCurrentIndex()
////        enabled: swipeView.currentIndex < swipeView.count - 1
////    }

//    SwipeView {
//        id: propertiesView
//        anchors.top: propertiesTabBar.bottom
//        anchors.right: parent.right
//        anchors.left: parent.left
//        anchors.topMargin: 0

//       currentIndex: propertiesTabBar.currentIndex

//        Item {
//            id: basePropertiesItem
////            anchors.fill: parent
////            visible: false
//            //            Column {
//            //                spacing: 10
//            //                anchors.topMargin: 20
//            //                anchors.bottomMargin: 20
//            //                anchors.rightMargin: 20
//            //                anchors.leftMargin: 20
//            //                anchors.fill: parent
//            Label {
//                text: "11111"
//            }
//            //            }
//        }
//        Item {
//            id: basePropertiesItem2
////            visible: false
////            anchors.fill: parent
//            //            Column {
//            //                spacing: 10
//            //                anchors.topMargin: 20
//            //                anchors.bottomMargin: 20
//            //                anchors.rightMargin: 20
//            //                anchors.leftMargin: 20
//            //                anchors.fill: parent
//            Label {
//                text: "2222"
//            }
//            //            }
//        }
//        PageIndicator {
//            id: propertiesIndicator
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 70
//            count: propertiesView.count
//            currentIndex: propertiesView.currentIndex
//            //                anchors.bottom: propertiesView.bottom
//            //                anchors.horizontalCenter: parent.horizontalCenter
//        }
//    }
}
