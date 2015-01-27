import QtQuick 2.0
import Sailfish.Silica 1.0

import JsonListModel 1.0

import "../helpers.js" as H

Page {
    id: showLights

    property variant bridgeApiUrl

    Label {
        id: messageLabel
        text: lightsModel.lastError
    }

    JsonListModel {
        id: lightsModel
        Component.onCompleted: {
            lightsModel.fetchUrl = bridgeApiUrl + "lights"
        }
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        anchors.top: messageLabel.bottom

        model: lightsModel

        header: PageHeader { title: qsTr("Lights") }

        ViewPlaceholder {
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
            onClicked: pageStack.push(Qt.resolvedUrl("BridgeInfo.qml"), { bridge: model })
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Refresh lights")
                onClicked: lightsModel.fetchJson()
            }
        }
    }
}
