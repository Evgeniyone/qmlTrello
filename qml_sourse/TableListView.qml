import QtQuick 2.0
import Tables 1.0
import QtQml.Models 2.3
Rectangle {
    color: "white"
    anchors.fill: parent
    border.color: "black"
    border.width: 2


    ListView{
        id:tables
        spacing: 4
        anchors.fill: parent
        model: TableListModel{
            id: tablesModel

        }
        delegate: Table{

        }

        orientation: ListView.Horizontal

    }
}
