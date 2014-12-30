import QtQuick 2.0
import Sailfish.Silica 1.0
import io.thp.pyotherside 1.3

Page {
    id: bridgeInfo

    property variant bridge

    SilicaFlickable {
        PageHeader {
            id: pageHeader
            title: qsTr("Bridge Info")
        }

        anchors.fill: parent
        contentHeight: column.height

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

        Python {
            id: py

            signal bridgeRegisterError(string message)
            signal bridgeRegistered
            signal registerBridge

            onError: {
                console.log('python: ' + traceback)
                messageLabel.text = "python: " + traceback
            }

            onBridgeRegistered: {
                console.log("onBridgeRegistered")
            }

            onBridgeRegisterError: {
                console.log("onBridgeRegisterError " + message)
                messageLabel.text = message
            }

            onRegisterBridge: {
                console.log("onRegisterBridge")
                py.call('bridgemodel.register_bridge', [bridge.internalipaddress], function(successful) {

                })
            }

            Component.onCompleted: {
                addImportPath(Qt.resolvedUrl('.'))

                setHandler('bridge-register-error', bridgeRegisterError)
                setHandler('bridge-registered', bridgeRegistered)

                importModule('bridgemodel', function() {
                    py.call('bridgemodel.is_bridge_registered', [bridge.internalipaddress], function(isRegistered) {
                        isRegisteredLabel.text = isRegistered ? qsTr("Registered") : qsTr("Not Registered")
                    })
                })
            }
        }
    }
}
