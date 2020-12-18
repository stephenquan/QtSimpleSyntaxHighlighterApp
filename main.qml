import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtSimpleSyntaxHighlighterApp 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QtSimpleSyntaxHighlighterApp")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextEdit {
                id: textEdit

                anchors.fill: parent

                text: [
                    "let a = 1;",
                    "let b = 2;",
                    "let c = 3;",
                    "let d = 4;",
                    "let e = 5;",
                ].join("\n") + "\n"
                selectByMouse: true

                Keys.onPressed: {
                    console.log("Keys.onPressed");
                }
            }
        }

        Button {
            text: qsTr("Patch")

            onClicked: {
                simpleSyntaxHighlighter.textDocument = null;
                simpleSyntaxHighlighter.textDocument = textEdit.textDocument;
            }
        }
    }

    SimpleSyntaxHighlighter {
        id: simpleSyntaxHighlighter
        textDocument: textEdit.textDocument
    }
}
