import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/jshue/src/jshue.js" as JsHue
import "../js/hue.js" as Hue

Page {
    id: lightDetail

    property var user
    property variant light
    property bool manualRefresh: false

    // debug
    Component.onCompleted: {
//        var hue = JsHue.jsHue()
//        user = hue.bridge('192.168.178.49').user('4940041b010273f7566238109b343bd280')
//        light = {
//            lightId: "2",
//            state: {
//                on: false,
//                bri: 0,
//                hue: 0,
//                sat: 0,
//                xy: [0, 0],
//                ct: 0,
//                alert: "none",
//                effect: "none",
//                colormode: "hs",
//                reachable: false
//            },
//            type: "Extended color light",
//            name: "Dirk Flur",
//            modelid: "LCT001",
//            uniqueid: "00:17:88:01:00:ba:9d:6f-0b",
//            swversion: "65003148",
//            pointsymbol: {
//                1: "none",
//                2: "none",
//                3: "none",
//                4: "none",
//                5: "none",
//                6: "none",
//                7: "none",
//                8: "none"
//            }
//        }
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

    function successStateFunction(stateName) {
        var name = stateName
        return function(state) {
//            console.log("state (" + stateName + ")", JSON.stringify(state))
            if (!checkErrors(state)) {
                var newLight = light;
                if (name) {
                    var newState = Hue.extractSingleStateValue(state, lightStateUrl(light.lightId, name));
                    newLight.state[stateName] = newState
                    light = newLight
                } else {
                    state.lightId = newLight.lightId
                    manualRefresh = true
                    light = state
                    manualRefresh = false
                }
            }
        }
    }

    function refreshLightState() {
        var lightId = light.lightId
        var success = successStateFunction()
        user.getLight(lightId, success, failure)
    }

    function lightStateUrl(lightId, propName) {
        return "/lights/" + lightId + "/state/" + propName
    }

    function lightToggle() {
        var success = successStateFunction("on")
        user.setLightState(light.lightId, {on: !light.state.on}, success, failure);
    }

    function sliderUpdateFunction(slider, name) {
//        console.log("sliderUpdateFunction", name, slider.value, manualRefresh)
        if (!manualRefresh) {
            var success = successStateFunction(name)
            var obj = {}
            obj[name] = slider.value
            user.setLightState(light.lightId, obj, success, failure);
        }
    }

    SilicaFlickable {
        PageHeader {
            id: pageHeader
            title: light.name + " (" + light.lightId + ")"
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
                text: qsTr("reachable: ") + light.state.reachable + qsTr(" alert: ") + light.state.alert + qsTr(" effect: ") + light.state.effect
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
                onClicked: lightToggle()
            }

            Slider {
                id: hueSlider
                width: parent.width
                minimumValue: 0
                maximumValue: 65280
                stepSize: 10
                valueText: "hue: " + hueSlider.value
                value: light.state.hue
                onValueChanged: sliderUpdateFunction(hueSlider, "hue")
            }

            Slider {
                id: satSlider
                width: parent.width
                minimumValue: 0
                maximumValue: 255
                stepSize: 1
                valueText: "sat: " + satSlider.value
                value: light.state.sat
                onValueChanged: sliderUpdateFunction(satSlider, "sat")
            }

            Slider {
                id: briSlider
                width: parent.width
                minimumValue: 0
                maximumValue: 255
                stepSize: 1
                valueText: "bri: " + briSlider.value
                value: light.state.bri
                onValueChanged: sliderUpdateFunction(briSlider, "bri")
            }

            Slider {
                id: ctSlider
                width: parent.width
                minimumValue: 153
                maximumValue: 500
                stepSize: 1
                valueText: "ct: " + ctSlider.value
                value: light.state.ct
                onValueChanged: sliderUpdateFunction(ctSlider, "ct")
            }

        }
        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Refresh State")
                onClicked: refreshLightState()
            }
        }
    }
}
