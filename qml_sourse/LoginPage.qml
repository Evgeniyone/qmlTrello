import QtQuick 2.4


    LoginPageForm{
        anchors.fill: parent
        roundButton.onClicked: {
            window.close()
            httprequest.autorization(login_input.text,password_input.text)
            table_window.show()

        }
}






