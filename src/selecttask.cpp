#include "selecttask.h"
#include "abstracttask.h"
#include "abstracttask.cpp"
#include "QVariant"
#include "QObject"
#include <QtSql>
#include <QHash>
#include <QFileInfo>
#include "threadchecker.h"
#include "database/databaseconnection.h"


SelectTask::SelectTask(QObject *parent): AbstractTask(parent){

}

const QVariant& SelectTask:: exequteTask(const QVariant &param) {
        ThreadChecker::logIfMainThread("handleSelectFileNames");
        QStringList list;
        const QString selectString = QString("SELECT * FROM logfiles;");

                QSqlQuery query(m_connections[m_currentFilePath]->database());
                if (!query.prepare(selectString)) {
                    qWarning() << "Wrong prepare operation! " << query.lastError().text();
                }

                if (!query.exec()) {
                    qWarning() << "Wrong select operation! " << query.lastError().text();
                }

                const int indexFileName = query.record().indexOf("filename");

                while(query.next()) {
                    const QString baseName = query.value(indexFileName).toString();

                    list.push_back(baseName);
                }
        QVariant q = QVariant::fromValue(list);
        return q;
    }


