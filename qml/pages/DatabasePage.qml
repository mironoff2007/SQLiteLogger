// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.auroraos.DatabaseModel 1.0
import ru.auroraos.DataBaseViewModel 1.0


Page {
    id: databasePage
    objectName: "databasePage"

    property string logFilePath

    function getFileName(path) {
        return path.split(/[\\\/]/).pop();
    }

    DatabaseModel {
        id: databaseModel

        onFileNames: function(list) {
            console.log("Current ListModel size:", list.length);
            fileNameModel.clear();
            for (var i = 0; i < list.length; i++) {
                fileNameModel.append({name: list[i]});
            }
        }
    }

    DataBaseViewModel {
            id: dbViewModel

            onSomeData: {
                console.log("Received data in QML:", list)
                fileNameModel.clear();
                for (var i = 0; i < list.length; i++) {
                    fileNameModel.append({name: list[i]});
                }
            }

            onSuccessState: function(state) {
                console.log("onSuccessState")
            }


        }

    ListModel {
        id: fileNameModel
    }

    ListModel {
        id: databaseFileNameModel

        ListElement {
            name: "db0.sqlite"
        }

        ListElement {
            name: "db1.sqlite"
        }

        ListElement {
            name: "db2.sqlite"
        }

        ListElement {
            name: "db3.sqlite"
        }
    }

    SilicaFlickable {
        id: flick

        anchors.fill: parent
        contentHeight: mainColumn.height

        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin

        Column {
            id: mainColumn

            width: parent.width

            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("SQLite")
            }

            ComboBox {
                id: comboBoxDatabases

                width: parent.width

                label: qsTr("Database: ")

                menu: ContextMenu {
                    Repeater {
                        model: databaseFileNameModel
                        MenuItem {
                            text: name

                            onClicked: {
                                databaseModel.databaseFilePath = text;
                            }
                        }
                    }
                }
            }

            TextArea {
                id: textAreaDatabaseFileName

                anchors {
                    left: parent.left;
                    right: parent.right
                }

                readOnly: true
            }

            SectionHeader {
                text: qsTr("Operations")
            }

            TextArea {
                id: textAreaLogFileName

                anchors {
                    left: parent.left;
                    right: parent.right
                }

                readOnly: true

                text: logFilePath
            }

            ButtonLayout {
                Button {
                    id: btnInsert

                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Insert")

                    onClicked: {
                        const basename = getFileName(logFilePath);
                        databaseModel.insertData(basename, logFilePath);
                    }
                }

                Button {
                    id: btnSelect

                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Select йоу")

                    onClicked: {
                        //databaseModel.selectData();
                        dbViewModel.generateSomeData();
                    }
                }
            }

            SectionHeader {
                text: qsTr("Log files:")
            }

            Repeater {
                id: repeater

                model: fileNameModel

                delegate: Label {
                    text: "прилетает сюда-" + name
                }
            }
        }
    }
}
