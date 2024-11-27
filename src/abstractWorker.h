#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H

#include <QThread>
#include "abstracttask.h"
#include "abstractbackgroundworker.h"
class  AbstractBackgroundWorker;

class AbstractWorker: public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorker(
            AbstractBackgroundWorker* worker,
            QObject *parent = nullptr
            );

    void startTask(const QVariant &param) {
        emit onMainCall(param);
    };

signals:
    void onMainCall(const QVariant &param);
    void resultTask(const QVariant &result);

private slots:
    void resultOnMain(const QVariant &result);


private:
    QScopedPointer<QThread> m_thread;
 public:
    AbstractBackgroundWorker *m_backgroundWorker;

};


#endif


