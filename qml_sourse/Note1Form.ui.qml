import QtQuick 2.4
import QtQuick.Controls 2.15

Item {
    width: 200
    height: 120

    Rectangle {
        id: rectangle
        color: "#bdc2e8"
        radius: 4
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#fdfbfb"
            }

            GradientStop {
                position: 1
                color: "#ebedee"
            }
        }
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0

        MouseArea {
            id: mouseArea
            height: 120
            anchors.fill: parent

            Text {
                id: text1
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                anchors.leftMargin: 0
                anchors.topMargin: 0
            }

            TextArea {
                id: textArea
                text: "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                placeholderText: ""
                font.pointSize: 12
                textFormat: Text.AutoText
                hoverEnabled: true
                baselineOffset: 19
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
            }
        }
    }
}
