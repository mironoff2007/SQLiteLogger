#ifndef ABSTRACTBACKGROUNDWORKER_H
#define ABSTRACTBACKGROUNDWORKER_H

#include <QObject>
#include "abstractWorker.h"


class AbstractBackgroundWorker : public QObject
{
    Q_OBJECT
public:
    explicit AbstractBackgroundWorker(
            AbstractTask* worker,
            QObject *parent = nullptr
            );

signals:
    void resultTask(const QVariant &result);

public slots:
    void runTaskOnBackGround(const QVariant &param);

public:
   AbstractTask *m_backgroundWorker;
};
#endif // ABSTRACTBACKGROUNDWORKER_H
