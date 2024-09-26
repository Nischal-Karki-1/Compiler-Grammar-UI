import QtQuick 2.15
import QtQuick.Window 2.15
import System 1.0

import "components/QuestionOne"
import "components/TopBar"
import "components/QuestionTwo"

Window {
    width: 960
    height: 720
    visible: true
    title: qsTr("Compiler Design")



    TopBar {
        id: topBar
    }

    Loader {
        id: mainLoader
        anchors {
            left: parent.left
            right: parent.right
            top: topBar.bottom
            bottom: parent.bottom
        }
        source:"components/QuestionOne/QuestionOne.qml"
    }

}
