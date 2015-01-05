import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: bridgeInfo

    property variant bridge

    SilicaFlickable {
        PageHeader {
            id: pageHeader
            title: qsTr("Bridge Info")
        }

        anchors.fill: parent

        Column {
            id: columnContents
            width: parent.width
            anchors.top: pageHeader.bottom
            spacing: 20
            anchors.leftMargin: 10
            x: Theme.paddingLarge

            Label { text: bridge.name }
            Label { text: bridge.internalipaddress }
            Label { text: bridge.id }
            Label { text: bridge.macaddress }
            Label {
                id: isRegisteredLabel
                text: qsTr("Registered: Unknown")
            }

            Label {
                id: messageLabel
                color: Theme.highlightColor
            }

            PullDownMenu {
                id: pullDownMenu
                MenuItem {
                    text: qsTr("Register")
                    onClicked: py.registerBridge();

                }
            }
        }
    }
}
