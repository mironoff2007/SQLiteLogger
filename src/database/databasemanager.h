// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "databaseservice.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& instance();

    void insert(const QString &filename, const QString &filepath);
    void selectFileNames();
    void setDatabase(const QString &filepath);

private:
    DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager() override = default;

signals:
    void fileNames(const QStringList &list);
    void databaseUpdated();

private slots:
    void onFileNames(const QStringList &list);
    void onDatabaseUpdated();

private:
    QScopedPointer<DatabaseService> m_service;
    QStringList m_fileNames;
};

#endif // DATABASEMANAGER_H
