// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "databasemodel.h"
#include "databasemanager.h"
#include <auroraapp/auroraapp.h>

namespace
{
    const auto defaultDatabaseName = QStringLiteral("db0.sqlite");

    auto appPath()
    {
        return Aurora::Application::filesDir(false).path();
    }
}

DatabaseModel::DatabaseModel(QObject *parent)
    : QObject(parent)
{
    m_manager = &DatabaseManager::instance();

    connect(m_manager, &DatabaseManager::fileNames, this, &DatabaseModel::onFileNames, Qt::QueuedConnection);
    connect(m_manager, &DatabaseManager::databaseUpdated, this, &DatabaseModel::onDatabaseUpdated, Qt::QueuedConnection);

    setDatabaseFilePath(defaultDatabaseName);
}

void DatabaseModel::insertData(const QString &filename, const QString &filepath)
{
    m_manager->insert(filename, filepath);
}

void DatabaseModel::selectData()
{
    m_manager->selectFileNames();
}

QString DatabaseModel::databaseFilePath() const
{
    return m_databaseFilePath;
}

void DatabaseModel::setDatabaseFilePath(const QString &filename)
{
    const auto filepath = QString("%1/%2").arg(appPath(), filename);
    if (filepath == m_databaseFilePath)
        return;

    m_databaseFilePath = filepath;
    m_manager->setDatabase(m_databaseFilePath);
}

void DatabaseModel::onFileNames(const QStringList &list)
{
    emit fileNames(list);
}

void DatabaseModel::onDatabaseUpdated()
{
    emit databaseFilePathChanged();
}
