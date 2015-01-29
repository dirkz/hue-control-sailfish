import QtQuick 2.0
import Sailfish.Silica 1.0

import BridgeUserModel 1.0

import "../js/jshue/src/jshue.js" as Hue
import "../js/helpers.js" as H

Page {
    id: bridgeInfo

    property variant bridge

    property string appName: "HueControl"
    property var hue: Hue.jsHue()
    property var user

    function registerBridge() {
        user.create(appName)
    }

    function checkRegistrationStatus() {
        user.getLights(function(lights) {
            console.log("have lights: " + JSON.stringify(lights))
            registrationStatusLabel.text = qsTr("Registered")
            messageLabel.text = ""
        },
        function(error) {
            registrationStatusLabel.text = qsTr("Not registered")
            messageLabel.text = error.message
        }
        )
    }

    BridgeUserModel {
        id: bridgeUserModel
        Component.onCompleted: {
            user = hue.bridge(bridge.internalipaddress).user(bridgeUserModel.userName)
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
                text: qsTr("Unknown")
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
                                                  bridgeApiUrl: bridgeModel.bridgeApiUrl
                                              })
                }
            }

            PushUpMenu {
                id: pushUpMenu
                MenuItem {
                    text: qsTr("Register")
                    onClicked: registerBridge();
                }
                MenuItem {
                    text: qsTr("Update Registration Status")
                    onClicked: checkRegistrationStatus();
                }
            }
        }
    }
}
