import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick 2.4
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.11

ApplicationWindow {
    visible: true
    width: 1200
    height: 700
    title: qsTr("Конфигуратор ДУТ (Beta 0.1)")
    View {
        id: view
        height: parent.height
        width: parent.width
    }
}
