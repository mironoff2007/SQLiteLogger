#ifndef SELECTTASK_H
#define SELECTTASK_H

#include "abstracttask.h"
#include <QtSql>
#include <QHash>
#include "abstractbackgroundworker.h"

class SelectTask : public AbstractBackgroundWorker
{
    Q_OBJECT

public:
    explicit SelectTask(QObject *parent = nullptr);

    const QVariant exequteTask(const QVariant &param) override;

public:
    QHash<QString, DatabaseConnection *> m_connections;
    QString m_currentFilePath;

    void setConnection(const QString &filepath){
        auto conn  = new DatabaseConnection(filepath);
        m_currentFilePath = filepath;
        m_connections.insert(filepath, conn);
    }
};

#endif // SELECTTASK_H
