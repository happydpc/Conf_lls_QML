import QtQuick.Controls 1.4
import QtQuick 2.9

TableViewColumn {
    id:tableColumn
    delegate: Rectangle {
        id:rectangle
        anchors.fill: parent
        color: inputValue.text.length >0 ? "transparent" : "red"
        TextInput {
            id:inputValue
            anchors.fill: parent
            selectionColor: "red"
            text: model[role]//(model[role]==="") ? "0" : model[role]
            validator: RegExpValidator { regExp: /[0-9A-F]+/ }
            onEditingFinished: {
                model[role] = text
//                remakeTarTableChart()
            }
        }
    }
}
