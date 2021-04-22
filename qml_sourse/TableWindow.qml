import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
ApplicationWindow {
    id : table_window
    title: qsTr("Your Table")
    width: Screen.width
    height: Screen.height


    //    Button{
    //        id:cliclme
    //        height: 100;
    //        width: 100;

    //        anchors.centerIn: parent
    //        onClicked: createObjecto()
    //    }
    Button {
        text: "Open"
        onClicked: popup.open()
    }

    Popup {
        id: popup
        //        x: 100
        y: 100
        width: 200
        height: 300
        modal: true
        focus: true
        property string texti: text_area1.text
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        ColumnLayout{
            TextArea {
                id: text_area1
                visible: true
                anchors { left: parent.left; right: parent.right }
                textFormat: Text.AutoText
                selectionColor: "#ffb7b7"
                text: "model.description"
                background: Rectangle{
                    color: "black"
                }


            }
            Button{
                onClicked: {text_area1.focus=false
                    popup.texti = text_area1.text
                popup.close()}
            }
        }





    }
    Table{

    }
}
