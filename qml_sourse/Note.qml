import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml.Models 2.3


Component {
    id: dragDelegate

    MouseArea {
        id: dragArea

        property bool held: false
        anchors { left: parent.left; right: parent.right }
        height: column.implicitHeight
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.target: held ? content : undefined
        drag.axis: Drag.YAxis
        onPressed:    {held = true; /*column.visible=true;et.visible=false*/}

        onClicked: {
            if (mouse.button == Qt.RightButton)
            {

                column.visible=true;
                et.visible=false
            }
        }

        onReleased: held = false


        Rectangle{

            id: content
            width: 200

            radius: 3
            Drag.active: dragArea.held
            Drag.source: dragArea
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            color: "white"

            anchors { left: parent.left; right: parent.right }
            anchors.margins: 5
            height: column.implicitHeight

            Text{

                id: et
                visible: true
                anchors.fill: parent
                font.pixelSize: 12
                anchors { left: parent.left; right: parent.right }
                anchors.topMargin: 5
                anchors.leftMargin: 7

                text: model.description
            }

            TextArea {
                id: column
                visible: false
                anchors { left: parent.left; right: parent.right }
                textFormat: Text.AutoText
                //                anchors.margins: 5

                text: model.description

                onEditingFinished : {

                    model.description = text
                    et.text=text
                    column.visible=false
                    et.visible=true

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



