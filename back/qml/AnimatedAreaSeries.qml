import QtQuick 2.0
import QtCharts 2.0

AreaSeries {
    id: series

    Behavior on opacity {
        NumberAnimation { duration: 250 }
    }
}
