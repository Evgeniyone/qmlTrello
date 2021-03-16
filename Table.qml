import QtQuick 2.4
import QtQuick.Controls 2.5
import Notes 1.0

TableForm {

    rectangle.height: {
        var a=table.contentHeight+dragArea.height+onHovered.height;
        if (a>window.height)
            return window.height;
        else return a;
    }

    table.model: NotesModel{}

    table.delegate:Item{

        width: table.width
        height: textin.implicitHeight

        TextArea {
            id: textin
            anchors.fill: parent
            text: model.description
            wrapMode: TextArea.Wrap

            background: Rectangle{
                color: "white"
                anchors.fill: parent
                radius: 10
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 5
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
