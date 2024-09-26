import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts 1.3
import Grammar 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    LRecursion {
        id: leftRecursion
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
                id: inputGrammar
                width: parent.width
                height: parent.height
                placeholderText: "Enter grammar rules here..."
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }

        Button {
            id: removeLeftRecursionButton
            text: "Remove Left Recursion"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 250
            Layout.preferredHeight: 60
            font.pixelSize: 16
            font.bold: true

            background: Rectangle {
                color: removeLeftRecursionButton.down ? "#A0A0A0" : "#D0D0D0"
                radius: 10
            }

            contentItem: Text {
                text: removeLeftRecursionButton.text
                font: removeLeftRecursionButton.font
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                outputGrammar.text = leftRecursion.removeLeftRecursion(inputGrammar.text)
            }
        }

        Text {
            text: "Output Grammar:"
            font.bold: true
            color: "white"
            font.pixelSize: 18
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            TextArea {
                id: outputGrammar
                width: parent.width
                height: parent.height
                placeholderText: "Output grammar will be displayed here..."
                readOnly: true
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }
    }
}
