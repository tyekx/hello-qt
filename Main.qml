import QtQuick
import QtQuick.Controls
import HelloContext 1.0

Window {

    HelloContext {
        id: helloContext
    }
    
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        text: "Click Me"
        anchors.centerIn: parent
        onClicked: {
            console.log(helloContext.greet("Dispatch from QML"));
        }
    }
}


