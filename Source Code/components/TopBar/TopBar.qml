import QtQuick 2.15
import System 1.0

Rectangle {
    id: topBar
    color: "black"
    height: parent.height / 8
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }

    System {
        id: systemHandler
    }

    // Bottom border
    Rectangle {
        width: parent.width
        height: 5
        color: "white"
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }

    Image {
        id: rect1
        width: 75
        height: 75
        source: systemHandler.questionOne ? "qrc:/components/assests/one_on.png" : "qrc:/components/assests/one_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(true)
                systemHandler.setQuestionTwo(false)
                systemHandler.setQuestionThree(false)
                systemHandler.setQuestionFour(false)
                systemHandler.setQuestionFive(false)
                systemHandler.setQuestionSix(false)
                mainLoader.source = "components/QuestionOne/QuestionOne.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: (parent.width - 6 * width) / 4
    }

    Image {
        id: rect2
        width: 75
        height: 75
        source: systemHandler.questionTwo ? "qrc:/components/assests/two_on.png" : "qrc:/components/assests/two_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(false)
                systemHandler.setQuestionTwo(true)
                systemHandler.setQuestionThree(false)
                systemHandler.setQuestionFour(false)
                systemHandler.setQuestionFive(false)
                systemHandler.setQuestionSix(false)
                mainLoader.source = "components/QuestionTwo/QuestionTwo.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: rect1.x + rect1.width + (parent.width - 6 * width) / 10
    }

    Image {
        id: rect3
        width: 75
        height: 75
        source: systemHandler.questionThree ? "qrc:/components/assests/three_on.png" : "qrc:/components/assests/three_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(false)
                systemHandler.setQuestionTwo(false)
                systemHandler.setQuestionThree(true)
                systemHandler.setQuestionFour(false)
                systemHandler.setQuestionFive(false)
                systemHandler.setQuestionSix(false)
                mainLoader.source = "components/QuestionThree/QuestionThree.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: rect2.x + rect2.width + (parent.width - 6 * width) / 10
    }

    Image {
        id: rect4
        width: 75
        height: 75
        source: systemHandler.questionFour ? "qrc:/components/assests/four_on.png" : "qrc:/components/assests/four_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(false)
                systemHandler.setQuestionTwo(false)
                systemHandler.setQuestionThree(false)
                systemHandler.setQuestionFour(true)
                systemHandler.setQuestionFive(false)
                systemHandler.setQuestionSix(false)
                mainLoader.source = "components/QuestionFour/QuestionFour.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: rect3.x + rect3.width + (parent.width - 6 * width) / 10
    }

    Image {
        id: rect5
        width: 75
        height: 75
        source: systemHandler.questionFive ? "qrc:/components/assests/five_on.png" : "qrc:/components/assests/five_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(false)
                systemHandler.setQuestionTwo(false)
                systemHandler.setQuestionThree(false)
                systemHandler.setQuestionFour(false)
                systemHandler.setQuestionFive(true)
                systemHandler.setQuestionSix(false)
                mainLoader.source = "components/QuestionFive/QuestionFive.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: rect4.x + rect4.width + (parent.width - 6 * width) / 10
    }

    Image {
        id: rect6
        width: 75
        height: 75
        source: systemHandler.questionSix ? "qrc:/components/assests/six_on.png" : "qrc:/components/assests/six_off.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                systemHandler.setQuestionOne(false)
                systemHandler.setQuestionTwo(false)
                systemHandler.setQuestionThree(false)
                systemHandler.setQuestionFour(false)
                systemHandler.setQuestionFive(false)
                systemHandler.setQuestionSix(true)
                mainLoader.source = "components/QuestionSix/QuestionSix.qml"
            }
        }
        anchors.verticalCenter: topBar.verticalCenter
        fillMode: Image.PreserveAspectFit
        x: rect5.x + rect5.width + (parent.width - 6 * width) / 10
    }
}
