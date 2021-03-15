import QtQuick 2.4
import QtQuick.Controls 2.5
import Notes 1.0

TableForm {

    table.model: NotesModel{}
    table.delegate:Item{

        width: table.width
        height: textin.implicitHeight
        TextEdit{
            id: textin
            text: model.description
            anchors.fill:parent
        }

    }
height: table.contentHeight+50
}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
