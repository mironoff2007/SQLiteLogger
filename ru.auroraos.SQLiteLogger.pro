# SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
# SPDX-License-Identifier: BSD-3-Clause

TARGET = ru.auroraos.SQLiteLogger

QT += sql

CONFIG += \
    auroraapp \

PKGCONFIG += \

SOURCES += \
    src/MyChildClass.cpp \
    src/MyParentClass.cpp \
    src/abstractWorker.cpp \
    src/database/databaseconnection.cpp \
    src/database/databasemanager.cpp \
    src/database/databasemodel.cpp \
    src/database/databaseservice.cpp \
    src/logger/applogger.cpp \
    src/logger/loggermodel.cpp \
    src/main.cpp \
    src/threadchecker.cpp

HEADERS += \
    src/abstractWorker.h \
    src/abstractbackgroundworker.h \
    src/abstracttask.h \
    src/database/databaseconnection.h \
    src/database/databasemanager.h \
    src/database/databasemodel.h \
    src/database/databaseservice.h \
    src/logger/applogger.h \
    src/logger/loggermodel.h \
    src/threadchecker.h

DISTFILES += \
    qml/pages/DatabaseUtils.qml \
    qml/pages/ViewPage.qml \
    rpm/ru.auroraos.SQLiteLogger.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-Clause.md \
    README.md \
    README.ru.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.SQLiteLogger.ts \
    translations/ru.auroraos.SQLiteLogger-ru.ts \
