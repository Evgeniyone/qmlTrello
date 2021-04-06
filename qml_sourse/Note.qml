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

        drag.target: held ? content : undefined
        drag.axis: Drag.YAxis
        onPressed:    {held = true; column.visible=true;et.visible=false}
        onReleased: held = false
        Rectangle{

            id: content
            border.width: 1
            border.color: "lightsteelblue"
            radius: 2
            Drag.active: dragArea.held
            Drag.source: dragArea
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            color: "white"

            anchors { left: parent.left; right: parent.right }
            height: column.implicitHeight


            states: State {
                when: dragArea.held

                ParentChange { target: content; parent: root }
                AnchorChanges {
                    target: content
                    anchors { horizontalCenter: undefined; verticalCenter: undefined }
                }
            }

        }
        Text{

            id: et
            visible: true
            anchors { left: parent.left; right: parent.right }
            anchors.margins: 5
            text: model.description
        }

        TextArea {
            id: column
            visible: false
            anchors { left: parent.left; right: parent.right }

            anchors.margins: 5

            text: model.description
            wrapMode: TextArea.Wrap
            onEditingFinished : {

                model.description = text
                et.text=text
                column.visible=false
                et.visible=true
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


//Item{

//    width: table.width
//    height: textin.implicitHeight

//    TextArea {
//        id: textin
//        anchors.fill: parent

//        text: model.description
//        wrapMode: TextArea.Wrap

//        onEditingFinished : {
//            model.description = text
//        }

//        background: Rectangle{
//            color: "white"
//            anchors.fill: parent
//            radius: 5
//            anchors.leftMargin: 10
//            anchors.rightMargin: 10
//            anchors.topMargin: 5
//            anchors.bottomMargin: 5
//        }
//    }
//}
