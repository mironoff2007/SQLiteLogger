// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.auroraos.LoggerModel 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    function getLogFileName(path) {
        return qsTr("File: <a href=\"file:/%1\">%1</a>").arg(path);
    }

    LoggerModel {
        id: loggerModel

        Component.onCompleted: {
            labelLogFile.text = getLogFileName(loggerModel.filePath);
        }

        onFilePathChanged: {
            labelLogFile.text = getLogFileName(loggerModel.filePath);
        }

        onDbusProcessResult: function (data) {
            textArea.text = data;
        }

        onLoggerTypeChanged: {
            const type = loggerModel.loggerType;
            if (type === 0) {
                rowWriteData.visible = true;
                textArea.text = "";
            } else {
                rowWriteData.visible = false;
            }
        }

        onAppEventResult: function (data) {
            textArea.text = data;
        }
    }

    SilicaFlickable {
        id: flick

        anchors.fill: parent
        contentHeight: mainColumn.height

        Column {
            id: mainColumn

            width: parent.width

            spacing: Theme.paddingMedium

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("SQLite Logger")
                extraContent.children: [
                    IconButton {
                        objectName: "aboutButton"
                        icon.source: "image://theme/icon-m-about"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                    }
                ]
            }

            SectionHeader {
                text: qsTr("Database")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter

                text: qsTr("Go to databases")

                onClicked: {
                    pageStack.push(Qt.resolvedUrl("DatabasePage.qml"), {logFilePath: loggerModel.filePath});
                }
            }

            SectionHeader {
                text: qsTr("Log file")
            }

            TextField {
                id: fieldLogFileName

                placeholderText: qsTr("Filename")
            }

            Button {
                id: buttonUpdateLogFileName

                anchors.horizontalCenter: parent.horizontalCenter

                text: qsTr("Update")

                onClicked: {
                    loggerModel.updateFileName(fieldLogFileName.text);
                }
            }

            Label {
                id: labelLogFile

                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }

                text: getLogFileName("")
                textFormat: Text.StyledText
                wrapMode: Text.Wrap
                linkColor: Theme.primaryColor
                onLinkActivated: Qt.openUrlExternally(link)
            }

            ComboBox {
                id: comboBoxLoggerType

                label: qsTr("Log type:")

                menu: ContextMenu {
                    Repeater {
                        model: loggerTypeModel
                        MenuItem {
                            text: title

                            onClicked: {
                                loggerModel.loggerType = index;
                            }
                        }
                    }
                }
            }

            Row {
                id: rowWriteData

                width: parent.width

                spacing: Theme.paddingMedium

                TextField {
                    id: fieldWriteToLog

                    width: parent.width - buttonSendData.width - Theme.paddingMedium

                    placeholderText: qsTr("Message")
                }

                IconButton {
                    id: buttonSendData

                    icon.source: "image://theme/icon-m-send"

                    onClicked: {
                        if (fieldLogFileName.text.length === 0)
                            return;

                        const data = fieldWriteToLog.text;
                        loggerModel.writeToLog(data);
                    }
                }
            }

            TextArea {
                id: textArea

                width: parent.width

                readOnly: true

                VerticalScrollDecorator {
                }
            }
        }

        ListModel {
            id: loggerTypeModel

            ListElement {
                title: qsTr("Write message to file")
                index: 0
            }

            ListElement {
                title: qsTr("DBus monitor")
                index: 1
            }

            ListElement {
                title: qsTr("Application events")
                index: 2
            }
        }
    }
}
