import QtQuick 2.4

PpoupForm {
    id: popup

    signal edFinish(string messages)
    saveButton.onClicked: {

        popup.edFinish(myNoteText.text)
        httprequest.sendNote(myNoteText.text)
        popup.close()

    }

}
