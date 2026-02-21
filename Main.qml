import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HelloContext 1.0

Window {

    HelloContext {
        id: helloContext
    }
    
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    RowLayout {

        anchors.fill: parent
        spacing: 0
            
        ColumnLayout {

            Layout.fillHeight: true
            Layout.preferredWidth: 320
            Layout.fillWidth: false
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 60

                color: "yellow"

                Text {
                    text: "Header"
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "green"

                TableView {
                    id: _tableView
                    anchors.fill: parent
                    columnSpacing: 0
                    rowSpacing: 0

                    model: MyTableModel {}

                    selectionBehavior: TableView.SelectCells
                    selectionModel: ItemSelectionModel {
                        id: _tableViewSelection
                        model: _tableView.model
                    }

                    delegate: Rectangle {
                        required property bool selected
                        required property int row
                        required property int column
                        implicitWidth: 120
                        implicitHeight: 32
                        color: selected ? "#87cefa" : "white"

                        Text {
                            text: display + ": " + selected
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                let index = _tableView.model.index(row, column)

                                _tableViewSelection.setCurrentIndex(index, ItemSelectionModel.NoUpdate)

                                _tableViewSelection.select(index, ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Rows)
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 60
                
                color: "yellow"

                Button {
                    text: "New Item"

                }
            }
        }

        Rectangle {

            Layout.fillWidth: true
            Layout.preferredWidth: 320
            Layout.fillHeight: true

            color: "orange"

        }

    }

}


