import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15
Rectangle{
    id: rectangle
    width: 250
    color: "#ebecf0"
    radius: 10
    property alias onHovered: onHovered
    property alias dragArea: dragArea
    property alias rectangle: rectangle
    property alias table: table

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
    Text {
        id: tableName
        text: qsTr("Text")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
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

        ScrollBar.vertical: ScrollBar {
            active: true
        }



    }

    MouseArea {
        id: dragArea
        height: 17
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        drag.target: rectangle
    }

    MouseArea{
        id:onHovered
        y: 82
        height: 18
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        hoverEnabled: true
        property bool hovered: false
        onEntered: hovered = true
        onExited: hovered = false

    }


    RoundButton {
        id: roundButton
        x: 0

        y: 82
        height: 18

        text: "+ Добавить новую карточку"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 8
        background: Rectangle{
            color: "#d9dce2"
            visible: onHovered.hovered || roundButton.hovered
            radius: 20
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff";formeditorZoom:1.100000023841858}
}
##^##*/
