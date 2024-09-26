import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Parser 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    FirstFollow {
        id: grammarParser
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 20

        Text {
            text: "Input Grammar:"
            font.bold: true
            color: "white"
            font.pixelSize: 18
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            TextArea {
                id: inputArea
                width: parent.width
                height: parent.height
                placeholderText: "Enter the grammar productions here..."
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }

        Button {
            id: calculateButton
            text: "Calculate First and Follow Sets"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 16
            font.bold: true

            background: Rectangle {
                color: calculateButton.down ? "#A0A0A0" : "#D0D0D0"
                radius: 10
            }

            contentItem: Text {
                text: calculateButton.text
                font: calculateButton.font
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                grammarParser.parseGrammar(inputArea.text)
                console.log( grammarParser.parseGrammar(inputArea.text))
            }
        }

        Text {
            text: "First Sets:"
            font.bold: true
            color: "white"
            font.pixelSize: 18
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            TextArea {
                id: firstOutputArea
                width: parent.width
                height: parent.height
                readOnly: true
                text: grammarParser.firstSets
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }

        Text {
            text: "Follow Sets:"
            font.bold: true
            color: "white"
            font.pixelSize: 18
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            TextArea {
                id: followOutputArea
                width: parent.width
                height: parent.height
                readOnly: true
                text: grammarParser.followSets
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }
    }
}
