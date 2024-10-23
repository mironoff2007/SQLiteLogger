// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection(const QString &filepath, QObject *parent)
    : QObject(parent)
    , m_name(QUuid::createUuid().toString())
    , m_filePath(filepath)
{
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
