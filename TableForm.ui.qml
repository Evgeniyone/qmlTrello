import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

ListView {

    id: table
    width: 300
    height: 150

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
    /*footer:*/    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 300
        height: 150
        color: "#e6e0e0"
        radius: 10
    }

    MouseArea {
        id: dragArea
        height: 29
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        drag.target: table
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0



    }

    ToolBar {
        id: toolBar
        height: 29
        position: ToolBar.Footer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0

        ToolButton {
            id: addNotes
            width: 179
            text: qsTr("Добавить новую карточку")
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            autoRepeat: false
            autoExclusive: false
            highlighted: false
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            padding: 0
            rightPadding: 0
            bottomPadding: 0
            leftPadding: 0
            topPadding: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //        position: ToolBar.Footer
    }

    Text {
        id: tableName
        text: qsTr("Text")
        anchors.fill: parent
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

}       /*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff";formeditorZoom:1.5}D{i:4}D{i:3}D{i:5}
}
##^##*/
