import QtQuick 2.5
import QtQuick.Controls 2.5
import GarageDoor 1.0
import "helpers"
import "helpers/util.js" as Helper

Rectangle {
    id: self

    width: page_width
    height: page_height

    property int page_width: 1
    property int page_height: 1
    property int failed: 0
    property bool needs_magic_key: false

    Component.onCompleted: {
        onCheckStatus()
    }

    function onCheckStatus()
    {
        ApiInterface.Control.request_challenge(
            function( challenge ){
                var answer = SharedState.challengeAnswer( challenge.challenge )

                ApiInterface.Control.door_status( answer,
                                                 function (resp)
                                                 {
                                                     failed = 0
                                                     toggleDoor.background.color = (resp.status? "green": "red")
                                                 },
                                                 function (err) {
                                                     toggleDoor.background.color = "gray"
                                                 })
            },
            function( err) {
            })
    }

    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: onCheckStatus()
    }

    RoundButton {
        id: toggleDoor

        anchors.margins: 15
        anchors.centerIn: self

        enabled: !needs_magic_key

        text: "Toggle Door"

        background: Rectangle {
            color: "gray"
            radius: 15
        }

        onClicked: {
            ApiInterface.Control.request_challenge(
                function( challenge ){
                    var answer = SharedState.challengeAnswer( challenge.challenge )

                    ApiInterface.Control.toggle_door(answer,
                                                     function (resp)
                                                     {
                                                         failed = 0
                                                         Mailbox.emitToast("Success", 2000)
                                                     },
                                                     function (err) {
                                                         needs_magic_key = (++failed >= 5)
                                                         Mailbox.emitToast("Failed: "+ err.reason, 2000)
                                                     })
                },
                function( err) {
                    needs_magic_key = (++failed >= 5)
                    Mailbox.emitToast("Failed: "+ err.reason, 2000)
                })
        }
    }

    Rectangle {
        id: magicContainer

        anchors.top: toggleDoor.bottom
        anchors.margins: 15
        anchors.left: self.left
        anchors.right: self.right

        radius: 5
        border.color: "blue"

        visible: needs_magic_key

        Label {
            id: magicLabel

            anchors.top: magicContainer.top
            anchors.horizontalCenter: magicContainer.horizontalCenter

            anchors.margins: 5

            text: "Enter Magic Key Challenge"
        }

        TextField {
            id: magicChallenge

            anchors.top: magicLabel.bottom
            anchors.left: magicChallenge.left
            anchors.right: magicSubmit.left
            anchors.margins: 5
        }

        RoundButton {
            id: magicSubmit

            anchors.top: magicLabel.bottom
            anchors.right: magicContainer.right
            anchors.margins: 5

            text: "Request"

            onClicked: {
                ApiInterface.Control.download_magic_key( magicChallenge.text,
                    function (magic) {
                        var sess = SharedState.getSession()
                        sess.magic_key = magic.magic_key
                        Mailbox.emitUpdateSession(sess)

                        Mailbox.emitToast("Successfully downloaded magic_key", 5000)
                        needs_magic_key = false
                    },
                    function(err){
                        Mailbox.emitToast("Couldn't download magic_key", 5000)
                    })
            }
        }
    }

}
