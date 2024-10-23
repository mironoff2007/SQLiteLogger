// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "databaseservice.h"
#include <QFileInfo>
#include "../threadchecker.h"

DatabaseService::DatabaseService(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
{
    auto worker = new DatabaseServiceWorker;
    worker->moveToThread(m_thread.data());

    connect(m_thread.data(), &QThread::finished, worker, &DatabaseServiceWorker::deleteLater);
    // Insert
    connect(this, &DatabaseService::operateInsert, worker, &DatabaseServiceWorker::handleInsert, Qt::QueuedConnection);
    // Select
    connect(this, &DatabaseService::operateSelectFileNames, worker, &DatabaseServiceWorker::handleSelectFileNames, Qt::QueuedConnection);
    connect(worker, &DatabaseServiceWorker::resultSelectFileNames, this, &DatabaseService::onResultSelectFileNames, Qt::QueuedConnection);
    // Setdatabase
    connect(this, &DatabaseService::operateSetDatabase, worker, &DatabaseServiceWorker::handleSetDatabase, Qt::QueuedConnection);
    connect(worker, &DatabaseServiceWorker::resultSetDatabase, this, &DatabaseService::onResultSetDatabase, Qt::QueuedConnection);

    m_thread->start();
}

DatabaseService::~DatabaseService()
{
    m_thread->quit();
    m_thread->wait();
}

void DatabaseService::insert(const QString &filename, const QString &filepath)
{
    emit operateInsert(filename, filepath);
}


void DatabaseService::selectFileNames()
{
    ThreadChecker::logIfMainThread("selectFileNames");
    emit operateSelectFileNames();//signal
}

void DatabaseService::setDatabase(const QString &filepath)
{
    emit operateSetDatabase(filepath);
}

void DatabaseService::onResultSelectFileNames(const QStringList &list)
{
    ThreadChecker::logIfMainThread("onResultSelectFileNames");
    emit fileNames(list);
}

void DatabaseService::onResultSetDatabase()
{
    emit databaseUpdated();
}

//////////////////////////// DatabaseServiceWorker

DatabaseServiceWorker::DatabaseServiceWorker(QObject *parent)
    : QObject(parent)
{

}

void DatabaseServiceWorker::createTable()
{
    QSqlQuery query(m_connections[m_currentFilePath]->database());
    if(!query.exec("CREATE TABLE IF NOT EXISTS logfiles("
                   " id TEXT PRIMARY KEY NOT NULL,"
                   " filename TEXT,"
                   " filepath TEXT);")) {
        qWarning() << "Error create table: " << query.lastError().text();
    }
}

void DatabaseServiceWorker::handleInsert(const QString &filename, const QString &filepath)
{
    const QString insertString = QString("INSERT INTO logfiles(id, filename, filepath) VALUES(:id, :filename, :filepath);");

    QSqlQuery query(m_connections[m_currentFilePath]->database());
    if (!query.prepare(insertString)) {
        qWarning() << "Wrong prepare operation! " + query.lastError().text();
        return;
    }

    const auto id = QUuid::createUuid().toString();

    query.bindValue(":id", id);
    query.bindValue(":filename", filename);
    query.bindValue(":filepath", filepath);

    if (!query.exec()) {
        qWarning() << "Wrong insert operation!" + query.lastError().text();;
    }
}

void DatabaseServiceWorker::handleSelectFileNames()
{
    ThreadChecker::logIfMainThread("handleSelectFileNames");
    QStringList list;

    const QString selectString = QString("SELECT * FROM logfiles;");

    QSqlQuery query(m_connections[m_currentFilePath]->database());
    if (!query.prepare(selectString)) {
        qWarning() << "Wrong prepare operation! " << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qWarning() << "Wrong select operation! " << query.lastError().text();
        return;
    }

    const int indexFileName = query.record().indexOf("filename");

    while(query.next()) {
        const QString baseName = query.value(indexFileName).toString();

        list.push_back(baseName);
    }

    emit resultSelectFileNames(list);
}

void DatabaseServiceWorker::handleSetDatabase(const QString &filepath)
{
    if (m_currentFilePath != filepath)
        m_currentFilePath = filepath;

    if (!m_connections.contains(filepath)) {
        auto conn  = new DatabaseConnection(filepath);
        m_connections.insert(filepath, conn);
    }

    createTable();

    emit resultSetDatabase();
}
