import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15
Rectangle{
    id: rectangle
    width: 250
    color: "#ebecf0"
    radius: 10
    property alias tableName: tableName
    property alias roundButton: roundButton
    property alias buttonAddNotes: buttonAddNotes
    property alias onHovered: onHovered
//    property alias dragArea: dragArea
    property alias rectangle: rectangle
    property alias table: table

//    Drag.active: dragArea.drag.active
//    Drag.hotSpot.x: 10
//    Drag.hotSpot.y: 10
    Text {
        id: tableName
        height: 33
        text: qsTr("Text")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 0
        anchors.leftMargin: 0
    }

    ListView {

        id: table
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tableName.bottom
        anchors.bottom: onHovered.top
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        clip: true
        spacing: 10

        ScrollBar.vertical: ScrollBar {
            active: true
        }



    }

//    MouseArea {
//        id: dragArea
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.bottom: table.top
//        drag.target: rectangle
//    }

    MouseArea{
        id:onHovered
        y: 82
        height: 18
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        hoverEnabled: true
        property bool hovered: false
        onEntered: hovered = true
        onExited: hovered = false

    }


    RoundButton {
        id: buttonAddNotes
        x: 0

        y: 82
        height: 18

        text: "+ Добавить новую карточку"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 10
        background: Rectangle{
            color: "#d9dce2"
            visible: onHovered.hovered || buttonAddNotes.hovered
            radius: 20
        }

    }

    RoundButton {
        id: roundButton
        x: 210
        y: 0
        width: 20
        height: 20
        text: "+"
        anchors.verticalCenter: tableName.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff";formeditorZoom:1.75}
}
##^##*/
