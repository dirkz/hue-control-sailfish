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

    function checkErrors(json) {
        var errors = Hue.errors(json)
        if (errors.length > 0) {
            messageLabel.text = Hue.errorDescriptions(json)
            registered = false
            return true
        } else {
            messageLabel.text = ""
            registered = true
            return false
        }
    }

    function registerBridge() {
        var success = function (result) {
            var ok = checkErrors(result)
        }
        var fail = function (error) {
            registered = false
            messageLabel.text = error.message
        }
        user.create(appName, success, fail)
    }

    function checkRegistrationStatus() {
        var success = function (lights) {
            checkErrors(lights)
        }
        var fail = function (error) {
            registered = false
            messageLabel.text = error.message
        }
        user.getLights(success, fail)
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
            anchors.leftMargin: 10
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
                text: "Mac: " + bridge.macaddress
            }

            Label {
                text: "Internal user:"
            }
            Label {
                text: bridgeUserModel.userName
            }
            Label {
                id: registrationStatusLabel
                text: registered ? qsTr("Registered") : qsTr("Not registered")
            }
            Label {
                id: messageLabel
                color: Theme.highlightColor
            }

            PullDownMenu {
                id: pullDownMenu
                MenuItem {
                    text: qsTr("Lights")
                    onClicked: pageStack.push(Qt.resolvedUrl("ShowLights.qml"),
                                              {
                                                  user: user
                                              })
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
