import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import Token 1.0

Rectangle {
    anchors.fill: parent
    color: "black"

    Tokenizer {
        id: tokenizer
    }

    Button {
        id: openFileButton
        text: "Open File Dialog"
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        width: 200
        height: 60
        font.pixelSize: 18
        font.bold: true

        background: Rectangle {
            color: openFileButton.down ? "#A0A0A0" : "#D0D0D0"
            radius: 10
        }

        contentItem: Text {
            text: openFileButton.text
            font: openFileButton.font
            color: "black"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: ["C++ files (*.cpp *.h)"]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            var token = tokenizer.tokenizeFile(fileDialog.selectedFile.toString().replace("file:///", ""))
            saveFileDialog.token = token
            saveFileDialog.open()
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    FileDialog {
        id: saveFileDialog
        title: "Save Tokenized Output"
        nameFilters: ["Text files (*.txt)"]
        fileMode: FileDialog.SaveFile
        property var token
        onAccepted: {
            tokenizer.writeTokensToFile(saveFileDialog.token, saveFileDialog.selectedFile.toString().replace("file:///", ""))
            console.log("File saved to " + saveFileDialog.selectedFile.toString().replace("file:///", ""))
        }
        onRejected: {
            console.log("Save canceled")
        }
    }
}
