import QtQuick 2.4

PpoupForm {
    id: popup

    signal edFinish(string messages)
    deleteButton.onClicked: {
        //httprequest.deleteNote(model.index)
        notes.list.deleteItem(model.index)
        popup.close()
}
    saveButton.onClicked: {

        popup.edFinish(myNoteText.text)
        console.log(model.index)
        console.log(root.indexOfTable)
        //httprequest.sendNote(model.index)
        popup.close()


    }


}
