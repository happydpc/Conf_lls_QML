import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: rectangle2
    color: "#e7e9eb"
    width: 500
    height: 500

    Item {
        id: rectangle
        clip: true
        anchors.fill: parent

        TableView {
            activeFocusOnTab: true
            alternatingRowColors: true
            backgroundVisible: true
            sortIndicatorColumn: 1
            verticalScrollBarPolicy: 3
            currentRow: 1
            highlightOnFocus: true
            anchors.fill: parent

            TableViewColumn {
                role: "date"    // These roles are roles names coincide with a C ++ model
                title: "Date"
            }

            TableViewColumn {
                role: "time"    // These roles are roles names coincide with a C ++ model
                title: "Time"
            }

            TableViewColumn {
                role: "random"  // These roles are roles names coincide with a C ++ model
                title: "Random"
            }

            TableViewColumn {
                role: "message" // These roles are roles names coincide with a C ++ model
                title: "Message"
            }

            // We set the model in the TableView
            model: myModel
        }
    }
}
