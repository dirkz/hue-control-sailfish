import QtQuick 2.0
import Sailfish.Silica 1.0

import BridgeUserModel 1.0

import "../js/jshue/src/jshue.js" as JsHue
import "../js/hue.js" as Hue

Page {
    id: bridgeInfo

    property variant bridge

    property string appName: "HueControl"
    property var hue: JsHue.jsHue()
    property var user
    property bool registered: false

    function registerBridge() {
        var success = function (result) {
            Hue.checkErrors(result, messageLabel)
        }
        var fail = function (error) {
            registered = false
            messageLabel.text = error.message
        }
        user.create(appName, success, fail)
    }

    function checkRegistrationStatus() {
        var success = function (lights) {
            var failed = Hue.checkErrors(lights, messageLabel)
            registered = !failed
        }
        var fail = function (error) {
            registered = false
            messageLabel.text = error.message
        }
        user.getLights(success, fail)
    }

    function showLights() {
        pageStack.push(Qt.resolvedUrl("ShowLights.qml"), {
                           user: user
                       })
    }

    BridgeUserModel {
        id: bridgeUserModel
        Component.onCompleted: {
            user = hue.bridge(bridge.internalipaddress).user(
                        bridgeUserModel.userName)
            checkRegistrationStatus()
        }
    }

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
            anchors.margins: Theme.paddingSmall
            x: Theme.paddingLarge

            Label {
                text: bridge.name
            }
            Label {
                text: "IP: " + bridge.internalipaddress
            }
            Label {
                text: "Id: " + bridge.id
            }

            Label {
                id: registrationStatusLabel
                text: Hue.encloseTag("b",
                                     registered ? qsTr("Registered") : qsTr(
                                                      "Not registered"))
            }

            Button {
                text: qsTr("Show Lights")
                onClicked: showLights()
                enabled: registered
            }

            Label {
                id: messageLabel
                color: Theme.highlightColor
            }

            PullDownMenu {
                id: pullDownMenu
                MenuItem {
                    text: qsTr("Lights")
                    onClicked: showLights()
                    enabled: registered
                }
            }

            PushUpMenu {
                id: pushUpMenu
                MenuItem {
                    text: qsTr("Register")
                    onClicked: registerBridge()
                    enabled: !registered
                }
                MenuItem {
                    text: qsTr("Update Registration Status")
                    onClicked: checkRegistrationStatus()
                }
            }
        }
    }
}
