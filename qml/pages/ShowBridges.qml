import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/helpers.js" as H
import "../js/jshue/src/jshue.js" as Hue

Page {
    id: showBridges

    property var hue: Hue.jsHue()

    function discoverBridges() {
        messageLabel.text = ""
        hue.discover(function (bridges) {
            listModel.clear()
            if (bridges.length === 0) {
                console.log("No bridges found")
                messageLabel.text = qsTr("No bridges found")
            } else {
                bridges.forEach(function (b) {
                    console.log("found bridge: ", b.internalipaddress)
                    listModel.append(b)
                })
            }
        }, function (error) {
            messageLabel.text += error.message
        })
    }

    Component.onCompleted: discoverBridges()

    Label {
        id: messageLabel
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        anchors.top: messageLabel.bottom

        model: ListModel {
            id: listModel
        }

        header: PageHeader {
            title: qsTr("Bridges")
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No bridges")
            hintText: qsTr("Pull down to add bridges")
        }

        delegate: ListItem {
            id: listItem
            Label {
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                x: Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                text: model.name + " (" + H.encloseTag(
                          "b", model.internalipaddress) + ")"
            }
            onClicked: pageStack.push(Qt.resolvedUrl("BridgeInfo.qml"), {
                                          bridge: model
                                      })
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Fetch Bridges")
                onClicked: discoverBridges()
            }
        }
    }
}
