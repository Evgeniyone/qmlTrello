import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    x: Screen.desktopAvailableWidth/2-width/2
    y: Screen.desktopAvailableHeight/2-height/2

    title: qsTr("Wou")



    LoginPage{
        anchors.fill: parent

    }

    TableWindow{
        id: table_window
    }

}
