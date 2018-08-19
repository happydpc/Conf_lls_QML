import QtQuick 2.9
import QtQuick.Controls 2.2

import timeGame 1.0
import settings 1.0

Control {
    id: name

    TimeGame {
        id: timeGame
        onUpdateTime: {
            viewForm.timeBar.text = dateTime
        }
    }

    Settings {
        id: settings
        onGetGamersCountChanged: {

        }
        onUpdateGamerCount: {
        }
    }

    ViewForm {
    }

}
