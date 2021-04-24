import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Popup {
    id: popup
    property string  noteText: ""

    signal edFinish(string messages)
    x: 100
    y: 100
    width: 200
    height: 300
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    ColumnLayout{
        TextArea{
            id: myNoteText
            text: noteText
        }
        Button{
            onClicked: {

                popup.noteText= myNoteText.text
                popup.edFinish(popup.noteText)
                popup.close()
            }
        }
    }


}
