import QtQuick 2.0
import Sailfish.Silica 1.0
import BridgeLoader 1.0

Page {
    id: showBridges

    RemorsePopup {
        id: clearRemorse
    }

    BridgeLoader {
        id: bridgeLoader
    }

    SilicaListView {

        id: listViewBridges
        anchors.fill: parent
        model: listModel

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
                onClicked: bridgeLoader.loadBridges()
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
                x: Theme.paddingLarge
                text: (model.index+1) + ". " + model.text
                anchors.verticalCenter: parent.verticalCenter
                font.capitalization: Font.Capitalize
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
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

