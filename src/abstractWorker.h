#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H

#include <QThread>
#include "abstractBackgroundWorker.h"

class AbstractWorker: public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorker(
            AbstractBackGroundWorker* worker,
            QObject *parent = nullptr
            );

    void startTask(const QVariant &param) {
        emit onMainCall(param);
    };

signals:void onMainCall(const QVariant &param);

private slots: void resultOnMain(const QVariant &result);


private:
    QScopedPointer<QThread> m_thread;
 public:
    AbstractBackGroundWorker *m_backgroundWorker;

};
#endif


