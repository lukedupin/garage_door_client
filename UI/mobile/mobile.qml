import QtQuick 2.13
import QtQuick.Controls 2.4
import GarageDoor 1.0
import "helpers"
import "helpers/util.js" as Helper

ApplicationWindow {
    id: appWindow

    Component.onCompleted: {
        Mailbox.pushForm.connect( appWindow.onPushForm )
        Mailbox.replaceForm.connect( appWindow.onReplaceForm )
        Mailbox.popForm.connect( appWindow.onPopForm )

        Mailbox.toast.connect( toast.show )
    }

    function onPushForm( qml_file, args )
    {
        if ( args === undefined || args === null )
            args = {}

        //Setup the display navigationBar
        stackView.displayNavigation = isRequireNavigation( qml_file )

        args["page_width"] = page.width
        args["page_height"] = page.height
        stackView.push( Qt.resolvedUrl("forms/"+ qml_file), args )
        stackView.qml_files.push( qml_file )

        //Emit the current item signal
        Mailbox.emitCurrentItem( qml_file, stackView.currentItem, stackView.qml_files.length )
    }

    function onReplaceForm( qml_file, args )
    {
        if ( args === undefined || args === null )
            args = {}

        //Setup the display navigationBar status
        stackView.displayNavigation = isRequireNavigation( qml_file )

        //Pop the stack
        while ( stackView.depth > 1 )
        {
            stackView.forceBackground = true
            stackView.pop()
            stackView.qml_files.pop()
        }

        //Push the new view
        args["page_width"] = page.width
        args["page_height"] = page.height
        stackView.push( Qt.resolvedUrl("forms/"+ qml_file), args )

        //Mimic what we're doing with the stack view
        stackView.qml_files.push( qml_file )

        //Emit the current item signal
        Mailbox.emitCurrentItem( qml_file, stackView.currentItem, stackView.qml_files.length )

        stackView.forceBackground = false
    }

    function onPopForm() {
        //Remove the entries
        stackView.qml_files.pop()

        //Send out the stack info
        if ( stackView.qml_files.length <= 0 )
        {
            //Check if we should be allowed to run
            if ( SharedState.getSession().auth === "" )
                close()

            stackView.displayNavigation = false
            Mailbox.emitCurrentItem( "Main.qml", main_form, stackView.qml_files.length )
        }
        else
        {
            stackView.displayNavigation = isRequireNavigation( stackView.qml_files[stackView.qml_files.length - 1] )
            Mailbox.emitCurrentItem( stackView.qml_files[stackView.qml_files.length - 1], stackView.currentItem, stackView.qml_files.length )
        }

        //Finally we want to pop the stack
        stackView.pop()
    }

    onClosing: {
        if ( stackView.depth > 1 )
        {
            close.accepted = false
            appWindow.onPopForm()
        }
    }

    title: qsTr("Garage Door")
    height: 640
    width: 360
    visible: true

    StackView {
        id: stackView
        anchors.top: titleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: navigationBar.top
        focus: true
        initialItem: Item {
            id: page
            StackView.visible: true
        }

        property variant qml_files: []

        property bool forceBackground: false
        property bool displayNavigation: false

        pushEnter: Transition {
            id: pushEnter
            //ParallelAnimation {
            SequentialAnimation {
                NumberAnimation { property: "opacity"; from: 0; to: 0.9; duration: 200 }

                PropertyAction { target: titleBar; property: "state"; value: (stackView.depth > 1 || stackView.forceBackground)? "SHOW": "HIDE" }
                PropertyAction { target: navigationBar; property: "state"; value: (stackView.depth > 1 && stackView.displayNavigation)? "SHOW": "HIDE" }
            }
        }

        popExit: Transition {
            id: popExit
            //ParallelAnimation {
            SequentialAnimation {
                NumberAnimation { property: "opacity"; from: 0.9; to: 0; duration: 300 }

                PropertyAction { target: titleBar; property: "state"; value: (stackView.depth > 1 || stackView.forceBackground)? "SHOW": "HIDE" }
                PropertyAction { target: navigationBar; property: "state"; value: (stackView.displayNavigation)? "SHOW": "HIDE" }
            }
        }

        pushExit: Transition {
            id: pushExit
        }

        popEnter: Transition {
            id: popEnter
        }
    }

    Main {
        id: main_form

    }

    ToastManager {
        id: toast
    }
}
