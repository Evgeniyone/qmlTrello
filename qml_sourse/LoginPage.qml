import QtQuick 2.4


    LoginPageForm{
        anchors.fill: parent
        roundButton.onClicked: {
            window.close()
            table_window.show()
            httprequest.autorization(login_input.text,password_input.text)
        }
}






