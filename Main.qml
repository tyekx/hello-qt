import QtQuick 6.4
import QtQuick.Controls 6.4
import QtQuick.Layouts 6.4
import HelloContext 1.0

Window {

    property var context: HelloContext {}
    
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        id: _button
        property var task: null

        text: (task) ? "Running: " + task.progress.toFixed(2) + "%" : "Start Task"
        onClicked: {
            if (!task) {
                task = context.dispatch()
            } else {
                task.cancel()
            }
        }

        Connections {
            target: _button.task
            function onFinished() {
                console.log("Task finished")
                _button.task = null
            }

            function onCanceled() {
                console.log("Task canceled")
                _button.task = null
            }
        }
    }

    Dialog {
        id: dialog
        title: "Title"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")
    }

}


