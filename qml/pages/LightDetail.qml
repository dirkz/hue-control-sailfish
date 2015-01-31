import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/jshue/src/jshue.js" as JsHue
import "../js/hue.js" as Hue

Page {
    id: lightDetail

    property var user
    property variant light
    property bool manualRefresh: false

    Component.onCompleted: {
        refreshLightState()
    }

    function failure(error) {
        messageLabel.text = error.message
        console.log(error.message)
    }

    function successStateFunction(stateName) {
        var name = stateName
        return function (state) {
            if (!Hue.checkErrors(state, messageLabel)) {
                var newLight = light
                if (name) {
                    var newState = Hue.extractSingleStateValue(
                                state, lightStateUrl(light.lightId, name))
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
        user.setLightState(light.lightId, {
                               on: !light.state.on
                           }, success, failure)
    }

    function sliderUpdateFunction(slider, name) {
        if (!manualRefresh) {
            var success = successStateFunction(name)
            var obj = {

            }
            obj[name] = slider.value
            user.setLightState(light.lightId, obj, success, failure)
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
            spacing: 10
            anchors.leftMargin: 10
            x: Theme.paddingSmall

            Label {
                text: qsTr("reachable: ") + light.state.reachable + qsTr(
                          " alert: ") + light.state.alert + qsTr(
                          " effect: ") + light.state.effect
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
