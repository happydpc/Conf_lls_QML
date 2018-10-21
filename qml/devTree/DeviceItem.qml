import QtQuick 2.0
import "qrc:/qml/devTree/"

Column{
    Repeater{
        model: modelData.childItems
        delegate: ItemView{}
    }
}
