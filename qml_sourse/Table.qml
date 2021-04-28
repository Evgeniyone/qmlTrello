import QtQuick 2.4
import QtQuick.Controls 2.5
import Notes 1.0
import QtQml.Models 2.3

TableForm {
    id:root
    roundButton.onClicked: {
        httprequest.sinchronize()

    }


    rectangle.height: {
        var a=table.contentHeight+dragArea.height+onHovered.height;
        if (a>table_window.height)
            return table_window.height;
        else return a;
    }


    DelegateModel {
        id: visualModel

        model: NotesModel {
            id:notes
            list: notesList
        }

        delegate: Note{}
    }


    table.model: visualModel

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
