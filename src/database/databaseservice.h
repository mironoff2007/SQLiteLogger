// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QObject>
#include <QThread>
#include <QtSql>
#include <QHash>
#include "databaseconnection.h"

class DatabaseService : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseService(QObject *parent = nullptr);
    ~DatabaseService() override;

    void insert(const QString &filename, const QString &filepath);
    void selectFileNames();
    void setDatabase(const QString &filepath);

signals:
    void operateInsert(const QString &filename, const QString &filepath);
    void operateSelectFileNames();
    void operateSetDatabase(const QString &filepath);

    void fileNames(const QStringList &list);
    void databaseUpdated();

private slots:
    void onResultSelectFileNames(const QStringList &list);
    void onResultSetDatabase();

private:
    QScopedPointer<QThread> m_thread;
};


//worker____________________
class DatabaseServiceWorker : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseServiceWorker(QObject *parent = nullptr);
    ~DatabaseServiceWorker() override = default;

private:
    void createTable();

signals:
    void resultSelectFileNames(const QStringList &list);
    void resultSetDatabase();

public slots:
    void handleInsert(const QString &filename, const QString &filepath);
    void handleSelectFileNames();

    void handleSetDatabase(const QString &filepath);

private:
    QHash<QString, DatabaseConnection *> m_connections;
    QString m_currentFilePath;
};

#endif // DATABASESERVICE_H
