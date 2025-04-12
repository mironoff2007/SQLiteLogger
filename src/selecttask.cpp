
#include "selecttask.h"
#include "abstractworker/abstracttask.h"
#include "QVariant"
#include "QObject"
#include <QtSql>
#include <QHash>
#include <QFileInfo>
#include "threadchecker.h"
#include "database/databaseconnection.h"
#include "abstractworker/abstractbackgroundworker.h"



SelectTask::SelectTask(QObject *parent): AbstractBackgroundWorker(parent) {

}


const QVariant SelectTask:: executeTask(const QVariant &param) {
    try {
        ThreadChecker::logIfMainThread("handleSelectFileNames");
        QStringList list;
        list.push_back("test1");
        const int size = list.size();
        qInfo() << "list size-" << size;

        ThreadChecker::logIfMainThread("handleSelectFileNames");

        const QString selectString = QString("SELECT * FROM logfiles;");

        QSqlQuery query(m_connections[m_currentFilePath]->database());
        if (!query.prepare(selectString)) {
            qWarning() << "Wrong prepare operation! " << query.lastError().text();
        }

        if (!query.exec()) {
            qWarning() << "Wrong select operation! " << query.lastError().text();
        }

        const int indexFileName = query.record().indexOf("filename");

        qInfo() << "while(query.next())";
        while(query.next()) {
            qInfo() << "next";
            const QString baseName = query.value(indexFileName).toString();
            list.push_back(baseName);
        }
        qInfo() << "list size-" << size;
        QVariant q = QVariant::fromValue(list);
        return q;
    }  catch (const std::exception &e) {
        qCritical() << "Exception in executeTask:" << e.what();
        return (QVariant());  // Emit empty QVariant on error
    }
}


