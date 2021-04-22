import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml.Models 2.3


Component {
    id: dragDelegate

    MouseArea {
        id: dragArea

        property bool held: false
        anchors { left: parent.left; right: parent.right }
        height: textAreaNote.implicitHeight
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.target: held ? content : undefined
        drag.axis: Drag.YAxis
        onPressed: held = true

        onClicked: {
            if (mouse.button == Qt.RightButton)
            {
                textAreaNote.visible=true;
                textNote.visible=false
            }
        }

        onReleased: held = false

        Rectangle{

            id: content
            width: 200
            height: textAreaNote.implicitHeight

            radius: 3
            Drag.active: dragArea.held
            Drag.source: dragArea
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            color: "white"

            anchors { left: parent.left; right: parent.right }
            anchors.margins: 5

            Text{

                id: textNote
                visible: true
                anchors.fill: parent
                font.pixelSize: 12
                anchors { left: parent.left; right: parent.right }
                anchors.topMargin: 5
                anchors.leftMargin: 7

                text: model.description
            }

            TextArea {
                id: textAreaNote
                visible: false
                anchors { left: parent.left; right: parent.right }
                textFormat: Text.AutoText


                text: model.description

                onEditingFinished : {

                    model.description = text
                    textNote.text=text
                    textAreaNote.visible=false
                    textNote.visible=true

                }
            }

            states: State {
                when: dragArea.held

                ParentChange { target: content; parent: root }
                AnchorChanges {
                    target: content
                    anchors { horizontalCenter: undefined; verticalCenter: undefined }
                }
            }

        }


        DropArea {
            anchors { fill: parent; margins: 10 }

            onEntered: {
                visualModel.items.move(
                            drag.source.DelegateModel.itemsIndex,
                            dragArea.DelegateModel.itemsIndex)
            }
        }
    }
}



