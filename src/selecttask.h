#ifndef SELECTTASK_H
#define SELECTTASK_H
#include "abstractworker/abstractbackgroundworker.h"
#include "abstractworker/abstracttask.h"
#include <QtSql>
#include <QHash>
#include "database/databaseConnection.h"

class SelectTask : public AbstractBackgroundWorker
{
    Q_OBJECT

public:
    explicit SelectTask(QObject *parent = nullptr);

    const QVariant executeTask(const QVariant &param) override;

public:
    QHash<QString, DatabaseConnection *> m_connections;
    QString m_currentFilePath;

    void setConnection(){
        auto conn  = new DatabaseConnection();
        m_currentFilePath = conn->filePath();
        m_connections.insert(m_currentFilePath, conn);
    }
};

#endif // SELECTTASK_H
