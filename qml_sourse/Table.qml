import QtQuick 2.4
import QtQuick.Controls 2.5
import Notes 1.0
import QtQml.Models 2.3

TableForm {
    id:root
    roundButton.onClicked: {
        //httprequest.sinchronize();
    }
    tableName.text:model.name

    rectangle.height: {
        var a=table.contentHeight+tableName.height+onHovered.height;
        if (a>table_window.height)
            return table_window.height-20;
        else return a;
    }


    DelegateModel {
        id: visualModel

        model: NotesModel {
            id:notes
            list:model.list
        }

        delegate: Note{}
    }


    table.model: visualModel

    buttonAddNotes.onClicked: {        
        notes.list.appendItem()

        table.positionViewAtEnd()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
