import QtQuick 2.0
import Sailfish.Silica 1.0
import BridgeLoader 1.0
import BridgeModel 1.0

Page {
    id: showBridges

    RemorsePopup {
        id: clearRemorse
    }

    BridgeModel {
        id: bridgeModel
    }

    BridgeLoader {
        id: bridgeLoader
        bridgeModel: bridgeModel
        onLoadBridgesError: messageLabel.text = errorMessage
        onLoadBridgesFinished: {
            messageLabel.text = jsonString
            console.log("bridges " + bridges)
            console.log("bridges.toJsonDocument().isArray() " + bridges.toJsonDocument().isArray())
            for (var i = 0; i < bridges.array().count(); ++i) {
                var value = bridges.at(i)
                console.log("bridge " + bridges)
            }
        }
    }

    Label {
        id: messageLabel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.horizontalCenter: parent.Center
        anchors.leftMargin: Theme.paddingSmall
        anchors.rightMargin: Theme.paddingSmall
    }

    SilicaListView {

        id: listViewBridges
        anchors.fill: parent
        model: bridgeModel

        header: PageHeader { title: qsTr("Bridges") }

        ViewPlaceholder {
            enabled: listViewBridges.count == 0
            text: qsTr("No bridges")
            hintText: qsTr("Pull down to add bridges")
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Jump to the end")
                visible: listViewBridges.count > 0
                onClicked: listView.scrollToBottom()
            }
            MenuItem {
                text: qsTr("Clear All")
                visible: listViewBridges.count > 0
                onClicked: clearRemorse.execute(qsTr("Clearing Bridges"), function() { listModel.clear() } )
            }
            MenuItem {
                text: qsTr("Load Bridges")
                onClicked: bridgeLoader.loadBridges(bridgeModel)
            }
            MenuLabel {
                text: qsTr("Bridges")
            }
        }
        PushUpMenu {
            id: pushUpMenu
            spacing: Theme.paddingLarge
            MenuItem {
                text: qsTr("Return to Top")
                onClicked: listView.scrollToTop()
                visible: listViewBridges.count > 0
            }
        }
        VerticalScrollDecorator {}

        delegate: ListItem {
            id: listItem
            menu: contextMenuComponent

            function remove() {
                remorseAction("Deleting", function() { listModel.remove(index) })
            }

            ListView.onRemove: animateRemoval()

            onClicked: {
                if (pageStack.depth == 2) {
                    pageStack.push(Qt.resolvedUrl("MenuPage.qml"))
                }
            }

            Label {
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                x: Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                text: model.ip + " (" + model.name + ")<br>" +
                model.bridgeId + " " + model.mac
            }

            Component {
                id: contextMenuComponent
                ContextMenu {
                    MenuItem {
                        text: qsTr("Delete")
                        onClicked: remove()
                    }
                }
            }
        }
    }

    ListModel {
        id: listModel
    }
}

