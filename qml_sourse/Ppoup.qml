import QtQuick 2.4

PpoupForm {
    id: popup

    signal edFinish(string messages)
    deleteButton.onClicked: {
        //httprequest.deleteNote(model.index)
        popup.close()
}
    saveButton.onClicked: {

        popup.edFinish(myNoteText.text)
        //httprequest.sendNote(model.index)
        popup.close()


    }


}
