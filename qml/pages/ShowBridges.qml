import QtQuick 2.0
import Sailfish.Silica 1.0
import io.thp.pyotherside 1.3

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
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.horizontalCenter: parent.Center
        anchors.leftMargin: Theme.paddingSmall
        anchors.rightMargin: Theme.paddingSmall
    }

    SilicaListView {
        id: listView
        anchors.fill: parent

        model: ListModel {
            id: listModel
        }

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
                text: model.name + " (" + encloseTag("b", model.internalipaddress) +
                      ")"
            }
        }

        PullDownMenu {
            id: pullDownMenu
            MenuItem {
                text: qsTr("Jump to the end")
                visible: listView.count > 0
                onClicked: listView.scrollToBottom()
            }
            MenuItem {
                text: qsTr("Fetch Bridges")
                onClicked: py.fetchBridges();

            }
        }
        PushUpMenu {
            id: pushUpMenu
            spacing: Theme.paddingLarge
            MenuItem {
                text: qsTr("Return to Top")
                onClicked: listView.scrollToTop()
                visible: listView.count > 0
            }
        }
    }

    Python {
        id: py

        signal fetchBridges
        signal bridgesFetched(variant bridges)

        onError: {
            console.log('Error: ' + traceback)
            messageLabel.text = "py error: " + traceback
        }

        onFetchBridges: {
            py.call('bridgemodel.fetch_bridges', []);
        }

        onBridgesFetched: {
            listModel.clear();
            for (var i = 0; i < bridges.length; i++) {
                listModel.append(bridges[i]);
            }
        }

        Component.onCompleted: {
            addImportPath(Qt.resolvedUrl('.'));

            setHandler('bridges-fetched', bridgesFetched)

            importModule('bridgemodel', function () {
                py.call('bridgemodel.fetch_bridges', []);
            });
        }
    }
}
