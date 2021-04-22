import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml.Models 2.3



Component {
    id: dragDelegate

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
//                text_area.visible=true;
//                texted.visible=false
//                createObjecto();
                popup.x=content.x
                popup.open()
                texted.text=popup.texti
//                text_area.selectAll()



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
                anchors.fill: parent
                font.pixelSize: 12
                anchors { left: parent.left; right: parent.right }
                anchors.topMargin: 5
                anchors.leftMargin: 7
                anchors.bottomMargin: 10

                text: model.description
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



