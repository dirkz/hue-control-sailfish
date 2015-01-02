import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: textAreaLogExample

    SilicaFlickable {
        TextArea {
            id: textAreaLog
            readOnly: true
            text: "Test"
            autoScrollEnabled: true
        }
    }

    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: {
            textAreaLog.text += "\n" + new Date().getUTCSeconds() + " Log"
        }
    }
}
