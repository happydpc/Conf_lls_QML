import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11

import QtQuick.Controls 1.4 as Controls_1_4

import "devices"

ApplicationWindow {
    visible: true
    width: 1200
    height: 680
//    visibility: "Maximized"
    title: qsTr("Конфигуратор Beta 0.2")
    View {
        id: view
        height: parent.height
        width: parent.width
    }
}
