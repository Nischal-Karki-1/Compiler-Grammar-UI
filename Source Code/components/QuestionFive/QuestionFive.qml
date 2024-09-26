import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import LParser 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    LL1 {
        id: parser
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextArea {
                id: inputArea
                Layout.fillWidth: true
                height: 50
                placeholderText: "Enter input string here..."
            }

            Button {
                id: parseButton
                text: "Parse"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth:  60
                Layout.preferredHeight: 30
                font.pixelSize: 14
                font.bold: true

                background: Rectangle {
                    color: parseButton.down ? "#A0A0A0" : "#D0D0D0"
                    radius: 5
                }

                contentItem: Text {
                    text: parseButton.text
                    font: parseButton.font
                    color: "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    var steps = parser.parse(inputArea.text + "$")
                    updateParseResults(steps)
                }
            }
        }

        Text {
            text: "Output:"
            font.bold: true
            font.pixelSize: 14
            color: "white"

        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 5

                Text {
                    text: "Stack"
                    font.bold: true
                    color:"white"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    TextArea {
                        id: stackArea
                        width: parent.width
                        height: parent.height
                        readOnly: true
                        wrapMode: TextArea.Wrap
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 5

                Text {
                    text: "Input"
                    font.bold: true
                    color: "white"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    TextArea {
                        id: input1Area
                        width: parent.width
                        height: parent.height
                        readOnly: true
                        wrapMode: TextArea.Wrap
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 5

                Text {
                    text: "Output"
                    font.bold: true
                    color: "white"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    TextArea {
                        id: outputArea
                        width: parent.width
                        height: parent.height
                        readOnly: true
                        wrapMode: TextArea.Wrap
                    }
                }
            }
        }

        Text {
            id: resultText
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 18
            font.bold: true
        }
    }

    Connections {
        target: parser
        function onParseCompleted(steps) {
            updateParseResults(steps)
        }
    }

    function updateParseResults(steps) {
        console.log("Parse completed:", steps[steps.length-1])
        stackArea.text = ""
        input1Area.text = ""
        outputArea.text = ""
        for (var i = 1; i < steps.length - 1; i++) {
            var parts = steps[i].split("\t\t\t")
            if (parts.length === 3) {
                stackArea.append(parts[0] + "\n")
                input1Area.append(parts[1] + "\n")
                outputArea.append(parts[2] + "\n")
            }
        }
        var statusMessage = steps[steps.length - 1]
        resultText.text = statusMessage
        resultText.color = statusMessage.toLowerCase().includes("success") ? "green" : "red"
    }
}
