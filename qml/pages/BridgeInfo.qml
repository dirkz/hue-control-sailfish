import QtQuick 2.0
import Sailfish.Silica 1.0

import BridgeRegistrationModel 1.0

Page {
    id: bridgeInfo

    property variant bridge

//    Item { // for debugging only
//        id: bridge
//        property string name: "Test"
//        property string internalipaddress: "192.168.178.22"
//    }

    BridgeRegistrationModel {
        id: bridgeModel
        bridgeIpAddress: bridge.internalipaddress
        Component.onCompleted: {
            updateRegistrationStatus()
        }
    }

    SilicaFlickable {
        PageHeader {
            id: pageHeader
            title: qsTr("Bridge Info")
        }

        anchors.fill: parent

        Column {
            id: columnContents
            width: parent.width
            anchors.top: pageHeader.bottom
            spacing: 20
            anchors.leftMargin: 10
            x: Theme.paddingLarge

            Label { text: bridge.name }
            Label { text: "IP: " + bridge.internalipaddress }
            Label { text: "Id: " + bridge.anId }
            Label { text: "Mac: " + bridge.macaddress }
            Label { text: "Internal user:" }
            Label { text: bridgeModel.userName }
            Label { text: "Registration status: " + bridgeModel.registrationStatus }

            Label {
                id: messageLabel
                color: Theme.highlightColor
                text: bridgeModel.lastError
            }

            PullDownMenu {
                id: pullDownMenu
                MenuItem {
                    text: qsTr("Register")
                    onClicked: py.registerBridge();

                }
            }
        }
    }
}
