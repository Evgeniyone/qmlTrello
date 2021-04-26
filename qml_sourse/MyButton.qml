import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    id: control

    contentItem: Text {
            text: control.text
            font.pointSize: 7
            opacity: enabled ? 1.0 : 0.3
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: control.down ? "black" : "#3f493f"
            border.width: 1
            radius: 5
            border.color: "#7d827d"
        }

}
