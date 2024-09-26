import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts 1.3
import Factor 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    LFactoring {
        id: leftFactoring
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
                placeholderText: "Enter grammar here..."
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }

        Button {
            id: removeLeftFactoringButton
            text: "Remove Left Factoring"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 250
            Layout.preferredHeight: 60
            font.pixelSize: 16
            font.bold: true

            background: Rectangle {
                color: removeLeftFactoringButton.down ? "#A0A0A0" : "#D0D0D0"
                radius: 10
            }

            contentItem: Text {
                text: removeLeftFactoringButton.text
                font: removeLeftFactoringButton.font
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                let productions = inputGrammar.text.split("\n");
                let result = leftFactoring.leftFactor(productions);
                outputGrammar.text = result.join("\n");
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
                placeholderText: "Left factored grammar will appear here..."
                readOnly: true
                wrapMode: TextEdit.Wrap
                font.pixelSize: 14
            }
        }
    }
}
