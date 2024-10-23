// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QAbstractListModel>

class DatabaseManager;

class DatabaseModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString databaseFilePath READ databaseFilePath WRITE setDatabaseFilePath NOTIFY databaseFilePathChanged)
public:
    explicit DatabaseModel(QObject *parent = nullptr);
    ~DatabaseModel() override = default;

    Q_INVOKABLE void insertData(const QString &filename, const QString &filepath);
    Q_INVOKABLE void selectData();

    QString databaseFilePath() const;
    void setDatabaseFilePath(const QString &filename);

private slots:
    void onFileNames(const QStringList &list);
    void onDatabaseUpdated();

signals:
    void fileNames(const QStringList &list);
    void databaseFilePathChanged();

private:
    QString m_databaseFilePath;
    DatabaseManager *m_manager = nullptr;
};

#endif // DATABASEMODEL_H
