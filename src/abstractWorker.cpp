#include "abstractWorker.h"
#include "abstractBackgroundWorker.h"
#include <QDebug>
#include "MyChildClass.cpp"

AbstractWorker::AbstractWorker(AbstractBackGroundWorker *worker, QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
    , m_backgroundWorker(worker)
{
    m_backgroundWorker->moveToThread(m_thread.data());

    //connect(this, &AbstractWorker::startTask, innerWorker, &AbstractBackGroundWorkerInner::runTaskOnBackGround, Qt::QueuedConnection);
    //connect(innerWorker, &AbstractBackGroundWorkerInner::resultTask, this, &AbstractWorker::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}

void AbstractWorker::resultOnMain(const QVariant &result)
{
    //emit databaseUpdated();
}




