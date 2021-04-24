import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml.Models 2.3


Component {
    id: dragDelegate

    MouseArea {
        id: dragArea

        property bool held: false

        anchors { left: parent.left; right: parent.right }
        height: content.height

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        drag.target: held ? content : undefined
        drag.axis: Drag.YAxis
        onPressed: held = true

        function setNoteText(message){
            textNote.text=message
        }

        function createObjecto()
        {
            var componento = Qt.createComponent("qrc:/qml_sourse/PopupNoteMenu.qml")
            var sprite = componento.createObject(table_window,{x:width+20,y:DelegateModel.itemsIndex*content.height});

            sprite.open()
            sprite.noteText = textNote.text
            sprite.edFinish.connect(setNoteText)

        }
        onClicked: {
            if (mouse.button == Qt.RightButton)
            {
                createObjecto()
            }
        }

        onReleased: held = false

        Rectangle{

            id: content
            width: 200
            height:50

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

                //                anchors.fill: parent
                font.pixelSize: 12
                anchors { left: parent.left; right: parent.right }
                anchors.topMargin: 5
                anchors.leftMargin: 7
                anchors.bottomMargin: 5
                text: model.description
                onContentHeightChanged: {
                    if(textNote.contentHeight>50)
                        content.height=textNote.contentHeight
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



