import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: textAreaLogExample

    TextArea {
        id: textAreaLog
        readOnly: true
        text: "Test"
    }

    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: {
            textAreaLog.text += "\n" + new Date().getUTCSeconds() + " Log " + textAreaLog.text.length
            textAreaLog.cursorPosition = textAreaLog.text.length - 1
        }
    }
}
