import QtQuick 2.4
import QtQuick.Controls 2.12

Popup {
    id: popup
    width: 300
    height: 250
    property alias deleteButton: deleteButton
    property alias saveButton: saveButton
    property alias myNoteText: myNoteText
    background: Rectangle{
        color: "white"
        opacity: 0.2
    }

    dim: true
    modal: true

    Column {
        id: column1
        anchors.left: flickable.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 5


        spacing: 10


        anchors.bottomMargin: 79


        MyButton{
            id: deleteButton
            height: 30
            text:qsTr("Удалить")
            anchors.left: parent.left
            anchors.right: parent.right
        }

        MyButton{
            height: 30
            text:qsTr("Копировать")
            anchors.left: parent.left
            anchors.right: parent.right
        }

        MyButton{
            height: 30
            text:qsTr("Переместить")
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.rightMargin: 95
        anchors.bottomMargin: 37

        TextArea.flickable: TextArea {
            id:myNoteText
            width: 199
            text: ""
            wrapMode: TextArea.Wrap
            background: Rectangle{
                color: "white"
                border.width: 2
                border.color:"#c8c4c4"
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }

    MyButton{
        id: saveButton
        x: 55
        y: 226
        width: 96
        height: 24
        text: qsTr("Сохранить")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
}
