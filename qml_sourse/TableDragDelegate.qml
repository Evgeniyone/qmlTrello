import QtQuick 2.0
import QtQml.Models 2.3

Component {
    MouseArea{
        id : dragAreaTable
        property bool held: false

        height: root.tableName.height
        width: content.width
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        drag.target: held ? content : undefined
        drag.axis: Drag.XandYAxis
        onPressed: held = true
        onReleased: held = false

        Rectangle{
            id:content
            height: root.height
            width: root.width
            opacity: 0.5
            Drag.active: dragAreaTable.held
            Drag.source: dragAreaTable
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2


            states: State {
                when: dragAreaTable.held

                ParentChange { target: content; parent: rootListView }
                AnchorChanges {
                    target: content
                    anchors { horizontalCenter: undefined; verticalCenter: undefined }
                }
            }
        }

        DropArea {
            id:dropaw
            property bool otherDraging: true
            width: root.width
            height: table_window.height
//            Rectangle{
//                anchors.fill: parent
//                color: "blue"
//            }
            Table{
                id: root

            }

            onEntered: {
                if(otherDraging)
                    visual.items.move(
                                drag.source.DelegateModel.itemsIndex,
                                dragAreaTable.DelegateModel.itemsIndex)

            }
        }


    }
}
