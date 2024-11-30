#ifndef SELECTTASK_H
#define SELECTTASK_H

#include "abstracttask.h"
#include <QtSql>
#include <QHash>
#include "database/databaseconnection.h"

class SelectTask : public AbstractTask
{
    Q_OBJECT

public:
    explicit SelectTask(QObject *parent = nullptr);

    const QVariant& exequteTask(const QVariant &param) override;


private:
    QHash<QString, DatabaseConnection *> m_connections;
    QString m_currentFilePath;
};

#endif // SELECTTASK_H
