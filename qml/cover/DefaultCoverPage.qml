// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    objectName: "defaultCover"

    CoverPlaceholder {
        objectName: "placeholder"
        text: qsTr("SQLite Logger")
        icon {
            source: Qt.resolvedUrl("../assets/SQLiteLogger.svg")
            sourceSize { 
                width: icon.width
                height: icon.height 
            }
        }
        forceFit: true
    }
}
