import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/jshue/src/jshue.js" as JsHue
import "../js/hue.js" as Hue

Page {
    id: lightDetail

    property var user
    property variant light

    // debug
    Component.onCompleted: {
        var hue = JsHue.jsHue()
        user = hue.bridge('192.168.178.49').user('4940041b010273f7566238109b343bd280')
        light = {
            lightId: "3",
            state: {
                on: false,
                bri: 0,
                hue: 0,
                sat: 0,
                xy: [0, 0],
                ct: 0,
                alert: "none",
                effect: "none",
                colormode: "hs",
                reachable: false
            },
            type: "Extended color light",
            name: "Dirk Flur",
            modelid: "LCT001",
            uniqueid: "00:17:88:01:00:ba:9d:6f-0b",
            swversion: "65003148",
            pointsymbol: {
                1: "none",
                2: "none",
                3: "none",
                4: "none",
                5: "none",
                6: "none",
                7: "none",
                8: "none"
            }
        }
        refreshLightState()
    }

    function checkErrors(json) {
        var errors = Hue.errors(json)
        if (errors.length > 0) {
            messageLabel.text = Hue.errorDescriptions(json)
            return true
        } else {
            messageLabel.text = ""
            return false
        }
    }

    function failure(error) {
        messageLabel.text = error.message
    }

    function refreshLightState() {
        var lightId = light.lightId
        var success = function(state) {
            if (!checkErrors(state)) {
                state.lightId = lightId
                light = state;
                console.log("read light ", JSON.stringify(light))
            }
        }
        user.getLight(lightId, success, failure)
    }

    function lightToggle() {
        var success = function(state) {
            console.log("state ", JSON.stringify(state))
            if (!checkErrors(state)) {
                var newLight = light;
                var obj = Hue.extractSingleStateValue(state, 'on');
                newLight.state.on = !light.state.on
                light = newLight
            }
        }
        user.setLightState(light.lightId, {on: !light.state.on}, success, failure);
    }

    SilicaFlickable {
        PageHeader {
            id: pageHeader
            title: light.name
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
                text: "id: " + light.lightId
            }
            Label {
                text: "reachable: " + light.state.reachable
            }
            Label {
                text: "bri: " + light.state.bri + " hue: " + light.state.hue +
                      " sat: " + light.state.sat
            }
            Label {
                text: "alert: " + light.state.alert + " effect: " + light.state.effect
            }

            Label {
                id: messageLabel
            }

            TextSwitch {
                id: onSwitch
                automaticCheck: false
                text: light.state.on ? qsTr("On") : qsTr("Off")
                description: qsTr("Light off/on")
                checked: light.state.on
                onClicked: {
                    lightToggle();
                }
            }
        }
        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Refresh")
                onClicked: refreshLightState()
            }
        }
    }
}
