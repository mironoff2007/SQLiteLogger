// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "databaseconnection.h"
#include <auroraapp/auroraapp.h>

namespace
{
    const auto defaultDatabaseName = QStringLiteral("db0.sqlite");

    auto appPath()
    {
        return Aurora::Application::filesDir(false).path();
    }
}


DatabaseConnection::DatabaseConnection(QObject *parent)
    : QObject(parent)
    , m_name(QUuid::createUuid().toString())
{
    const auto filepath = QString("%1/%2").arg(appPath(), defaultDatabaseName);
    m_filePath = filepath;
    auto database = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), m_name);
    database.setDatabaseName(m_filePath);
    database.open();
}

DatabaseConnection::~DatabaseConnection()
{
    QSqlDatabase::removeDatabase(m_name);
}

QSqlDatabase DatabaseConnection::database() const
{
    return QSqlDatabase::database(m_name);
}

QString DatabaseConnection::connectionName() const
{
    return m_name;
}

QString DatabaseConnection::filePath() const
{
    return m_filePath;
}
