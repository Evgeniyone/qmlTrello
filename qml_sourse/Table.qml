import QtQuick 2.4
import QtQuick.Controls 2.5
import Notes 1.0


TableForm {


    rectangle.height: {
        var a=table.contentHeight+dragArea.height+onHovered.height;
        if (a>table_window.height)
            return table_window.height;
        else return a;
    }



    table.model: NotesModel{
        id:notes
    }

    table.delegate:Item{

        width: table.width
        height: textin.implicitHeight

        TextArea {
            id: textin
            anchors.fill: parent

            text: model.description
            wrapMode: TextArea.Wrap

            onEditingFinished : {
                model.description = text
            }

            background: Rectangle{
                color: "white"
                anchors.fill: parent
                radius: 5
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 5
                anchors.bottomMargin: 5
            }
        }
    }

    buttonAddNotes.onClicked: {

        table.positionViewAtEnd()
        notes.list.appendItem()

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
