import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/jshue/src/jshue.js" as JsHue
import "../js/hue.js" as Hue

Page {
    id: showLights

    property var user

    function checkErrors(json) {
        var errors = Hue.errors(json)
        if (errors.length > 0) {
            lightsPlaceHolder.text = Hue.errorDescriptions(json)
            return true
        } else {
            return false
        }
    }

    function fetchLights() {
        var success = function (lights) {
            if (!checkErrors(lights)) {
                listModel.clear()
                var list = Hue.lightsList(lights)
                list.forEach(function (l) {
                    listModel.append(l)
                })
            }
        }
        var fail = function (error) {
            lightsPlaceHolder.text = error.message
        }
        user.getLights(success, fail)
    }

    Component.onCompleted: fetchLights()

    SilicaListView {
        id: listView
        anchors.fill: parent

        model: ListModel {
            id: listModel
        }

        header: PageHeader {
            title: qsTr("Lights")
        }

        ViewPlaceholder {
            id: lightsPlaceHolder
            enabled: listView.count == 0
            text: qsTr("No lights loaded")
            hintText: qsTr("Pull down to refresh")
        }

        delegate: ListItem {
            id: listItem
            Label {
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                x: Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                text: model.name
            }
            onClicked: pageStack.push(Qt.resolvedUrl("LightDetail.qml"), {
                                          user: user,
                                          light: {
                                              lightId: model.lightId,
                                              reachable: false,
                                              state: {
                                                  on: false,
                                                  hue: 0,
                                                  bri: 0,
                                                  sat: 0,
                                                  ct: 0
                                              }
                                          }
                                      })
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Refresh lights")
                onClicked: fetchLights()
            }
        }
    }
}
