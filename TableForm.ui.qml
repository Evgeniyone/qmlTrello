import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Rectangle {

    id: item1
    width: 300
    height: 150
    property alias nameFontfamily: name.font.family
    property alias toolButton: toolButton
    color: "#f0f0f0"

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10

    MouseArea {
        id: dragArea
        height: 29
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        drag.target: parent

        Rectangle {
            id: rectangle
            color: "#e5dddd"
            anchors.fill: parent
            anchors.bottomMargin: 0
        }
    }



    ToolBar {
        id: toolBar
        y: 67
        height: 33
        position: ToolBar.Footer
        Text {
            id: name
            text: qsTr("Добавить новую карточку")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            anchors.leftMargin: 16
            anchors.bottomMargin: 5
            anchors.topMargin: 7


        }
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        RoundButton {
            id: toolButton
            x: 180
            width: 20
            radius: 26
            text: qsTr("+")
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.rightMargin: 3
            anchors.topMargin: 7
            highlighted: true

            background:Rectangle{
                color: "#808080"
                radius: 5
            }

        }


    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
