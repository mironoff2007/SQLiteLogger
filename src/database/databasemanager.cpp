// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "databasemanager.h"
#include <auroraapp/auroraapp.h>
#include "../threadchecker.h"

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager manager;
    return manager;
}

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
    , m_service(new DatabaseService)
{
    connect(m_service.data(), &DatabaseService::fileNames, this, &DatabaseManager::onFileNames, Qt::QueuedConnection);
    connect(m_service.data(), &DatabaseService::databaseUpdated, this, &DatabaseManager::onDatabaseUpdated, Qt::QueuedConnection);
}

void DatabaseManager::insert(const QString &filename, const QString &filepath)
{
    m_service->insert(filename, filepath);
}

void DatabaseManager::selectFileNames()
{
    ThreadChecker::logIfMainThread("DatabaseManager");
    m_service->selectFileNames();
}

void DatabaseManager::setDatabase(const QString &filepath)
{
    m_service->setDatabase(filepath);
}

void DatabaseManager::onFileNames(const QStringList &list)
{
    m_fileNames.clear();
    m_fileNames = list;

    emit fileNames(list);
}

void DatabaseManager::onDatabaseUpdated()
{
    emit databaseUpdated();
}
