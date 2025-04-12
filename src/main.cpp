// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include <auroraapp.h>
#include <QtQuick>

#include "database/databasemodel.h"
#include "logger/loggermodel.h"
#include "logger/applogger.h"
#include "databaseviewmodel.h"
#include "abstractviewmodel.h"

#include "state.h"
#include "person.h"


int main(int argc, char *argv[])
{
    AppLogger::instance().init();

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("SQLiteLogger"));

    qmlRegisterType<LoggerModel>("ru.auroraos.LoggerModel", 1, 0, "LoggerModel");
    qmlRegisterType<DatabaseModel>("ru.auroraos.DatabaseModel", 1, 0, "DatabaseModel");
    qmlRegisterType<AbstractDataBaseViewModel>("ru.auroraos.AbstractDataBaseViewModel", 1, 0, "AbstractDataBaseViewModel");
    qmlRegisterType<DataBaseViewModel>("ru.auroraos.DataBaseViewModel", 1, 0, "DataBaseViewModel");
    qmlRegisterType<Person>("ru.auroraos.Person", 1, 0, "Person");
    //qmlRegisterType<State>("ru.auroraos.State", 1, 0, "State");


    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/SQLiteLogger.qml")));
    view->show();

    return application->exec();
}
