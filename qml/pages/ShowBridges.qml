import QtQuick 2.0
import Sailfish.Silica 1.0

import JsonListModel 1.0

Page {
    id: showBridges

    function encloseTag(tag, s) {
        return "<" + tag + ">" + s + "</" + tag + ">";
    }

    function lineBreak() {
        return "<br>"
    }

    Label {
        id: messageLabel
        text: bridgeModel.lastError
    }

    JsonListModel {
        id: bridgeModel
        Component.onCompleted: {
            bridgeModel.fetchUrl = "https://www.meethue.com/api/nupnp"
        }
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        anchors.top: messageLabel.bottom

        model: bridgeModel

        header: PageHeader { title: qsTr("Bridges") }

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
                text: model.name + " (" + encloseTag("b", model.internalipaddress) + ")"
            }
            onClicked: pageStack.push(Qt.resolvedUrl("BridgeInfo.qml"), { bridge: model })
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Fetch Bridges")
                onClicked: bridgeModel.fetchJson()
            }
        }
    }
}
