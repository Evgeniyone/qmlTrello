import QtQuick 2.0
import Tables 1.0
import QtQml.Models 2.3
import QtQuick.Controls 2.12
Rectangle {
    id: rootListView
    color: "white"
    anchors{top:parent.top;bottom: parent.bottom;left:parent.left}
    width: tables.contentWidth
    border.color: "black"
    border.width: 2
    Button{
        width: 100
        height: 40
        y:30
        text: qsTr("Добавить Таблицу")
        anchors.leftMargin: 50
        anchors.left:tables.right
        onClicked: tablesModel.list.appendItem()
    }

    DelegateModel {
        id: visual

        model: TableListModel{
            id: tablesModel

        }

        delegate: TableDragDelegate{

        }
    }
    ListView{
        id:tables
        spacing: 10
        anchors.fill: parent
        anchors.margins: 15

        model:visual
        orientation: ListView.Horizontal

    }
}
