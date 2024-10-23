// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QObject>
#include <QUuid>
#include <QtSql>

class DatabaseConnection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DatabaseConnection)
public:
    DatabaseConnection(const QString &filepath, QObject *parent = nullptr);

    ~DatabaseConnection() override;

    QSqlDatabase database() const;

    QString connectionName() const;

    QString filePath() const;

private:
    QString m_name;
    QString m_filePath;
};

#endif // DATABASECONNECTION_H
