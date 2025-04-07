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
#include "abstractbackgroundworker.cpp"


SelectTask::SelectTask(QObject *parent): AbstractBackgroundWorker(parent){

}


const QVariant SelectTask:: exequteTask(const QVariant &param) {
    try {
        ThreadChecker::logIfMainThread("handleSelectFileNames");
        QStringList list;
        list.push_back("test1");
        const int size = list.size();
        qInfo() << "list size-" << size;
        QVariant q = QVariant::fromValue(list);
        QStringList retrievedList = q.value<QStringList>();
        qDebug() << "List size:" << retrievedList.size();
        return q;
    }  catch (const std::exception &e) {
        qCritical() << "Exception in executeTask:" << e.what();
        return (QVariant());  // Emit empty QVariant on error
    }
}


