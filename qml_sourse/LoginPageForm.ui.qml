import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0

Item {
    id: login_page
    property alias roundButton: roundButton
    property alias login_input: login_input
    property alias password_input: password_input

    Image {
        id: login_background
        anchors.fill: parent
        source: "../image/login_background.jpg"
        fillMode: Image.Stretch
    }

    Rectangle {
        id: rectangle
        x: 256
        y: 180
        width: 350
        height: 240
        opacity: 0.6
        radius: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            id: column
            y: 96
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            spacing: 5

            TextField {
                id: login_input
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                placeholderText: qsTr("Login")
            }

            TextField {
                id: password_input
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                echoMode: "Password"
                placeholderText: qsTr("Password")
            }
        }

        RoundButton {
            id: roundButton
            text: "Sign In"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: column.bottom
            anchors.rightMargin: 30
            anchors.leftMargin: 30
            anchors.topMargin: 11
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
