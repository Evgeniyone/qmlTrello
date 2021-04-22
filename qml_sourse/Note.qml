import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml.Models 2.3



Component {
//    id:myNote
//    height: texted.implicitHeight
//    width: 200
//    color: "white"
    MouseArea {
        id: dragArea

        function createObjecto()
        {
            var componento = Qt.createComponent("qrc:/qml_sourse/contexNoteMenu.qml")
            var sprite = componento.createObject(table_window,{x:width+20,y:DelegateModel.itemsIndex*content.height});
            console.log(DelegateModel.itemsIndex)

        }

        property bool held: false
        anchors { left: parent.left; right: parent.right }
        height: texted.implicitHeight
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.target: held ? content : undefined
        drag.axis: Drag.YAxis

        onPressed:    held = true

        onClicked: {
            if (mouse.button == Qt.RightButton)
            {

                popup.x=content.x
                popup.texti=texted.text
                popup.open()
//                texted.text=myTable.noteText





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
            height: texted.implicitHeight

            Text{

                id: texted
                visible: true
                //                anchors.fill: parent
                font.pixelSize: 12
                anchors { left: parent.left; right: parent.right }

                text: model.description
                onFocusChanged: model.description = text
            }

            //            TextArea {
            //                id: text_area
            //                visible: false
            //                anchors { left: parent.left; right: parent.right }
            //                textFormat: Text.AutoText
            //                selectionColor: "#ffb7b7"
            //                text: model.description

            //                onEditingFinished : {

            //                    model.description = text
            //                    texted.text=text
            //                    text_area.visible=false
            //                    texted.visible=true

            //                }
            //            }

            states: State {
                when: dragArea.held

                ParentChange { target: content; parent: myTable }
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



