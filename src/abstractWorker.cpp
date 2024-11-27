#include "abstractWorker.h"
#include "abstracttask.h"
#include <QDebug>
#include "MyChildClass.cpp"

AbstractWorker::AbstractWorker(AbstractBackgroundWorker *worker, QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
    , m_backgroundWorker(worker)
{
    m_backgroundWorker->moveToThread(m_thread.data());

    connect(this, &AbstractWorker::startTask, m_backgroundWorker,&AbstractBackgroundWorker::runTaskOnBackGround, Qt::QueuedConnection);
    connect(m_backgroundWorker, &AbstractBackgroundWorker::resultTask, this, &AbstractWorker::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}

void AbstractWorker::resultOnMain(const QVariant &result)
{
    emit resultTask(result);
}

AbstractBackgroundWorker::AbstractBackgroundWorker(AbstractTask *worker, QObject *parent)
    : QObject(parent)
   , m_backgroundWorker(worker)
{

}


void AbstractBackgroundWorker::runTaskOnBackGround(const QVariant &param) {
   emit resultTask( m_backgroundWorker->exequteTask(param));
}





