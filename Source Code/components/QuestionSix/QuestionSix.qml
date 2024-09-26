import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import LRParser 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    LR {
        id: lrparser
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextArea {
                id: inputTextArea
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
                    lrparser.inputString = inputTextArea.text
                    lrparser.parse()
                    updateAcceptanceStatus()
                }
            }
        }

        Text {
            text: "Output:"
            font.bold: true
            font.pixelSize: 14
            color:"white"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 20

            Repeater {
                model: ["Stack", "Input", "Action"]
                delegate: ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 5

                    Text {
                        text: modelData
                        font.bold: true
                        color:"white"
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        TextArea {
                            width: parent.width
                            height: parent.height
                            readOnly: true
                            text: {
                                if (modelData === "Stack") return lrparser.stack.join("\n")
                                if (modelData === "Input") return lrparser.input.join("\n")
                                if (modelData === "Action") return lrparser.action.join("\n")
                                return ""
                            }
                            wrapMode: TextEdit.Wrap
                        }
                    }
                }
            }
        }

        Text {
            id: acceptanceStatus
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 18
            font.bold: true
        }
    }

    function updateAcceptanceStatus() {
        let actions = lrparser.action
        if (actions.length > 0) {
            let lastAction = actions[actions.length - 1]
            if (lastAction.toLowerCase().includes("accept")) {
                acceptanceStatus.text = "String Accepted"
                acceptanceStatus.color = "green"
            } else {
                acceptanceStatus.text = "String Rejected"
                acceptanceStatus.color = "red"
            }
        } else {
            acceptanceStatus.text = ""
        }
    }
}
