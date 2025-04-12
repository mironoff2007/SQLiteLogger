#include "abstractWorker.h"
#include "abstracttask.h"
#include <QDebug>

AbstractWorker::AbstractWorker(AbstractBackgroundWorker *worker, QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
    , m_backgroundWorker(worker)
{
    m_backgroundWorker->moveToThread(m_thread.data());

    connect(this, &AbstractWorker::onMainCall, m_backgroundWorker,&AbstractBackgroundWorker::runTaskOnBackGround, Qt::QueuedConnection);
    connect(m_backgroundWorker, &AbstractBackgroundWorker::resultBackgroundTask, this, &AbstractWorker::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}

void AbstractWorker::resultOnMain(const QVariant &result)
{
    emit resultTask(result);
}


void AbstractBackgroundWorker::runTaskOnBackGround(const QVariant &param) {
    try {
        const QVariant result = this->executeTask(param);
        emit resultBackgroundTask(result);
    }
    catch (const std::exception &e) {
        qCritical() << "Exception in executeTask:" << e.what();
        emit resultBackgroundTask(QVariant());  // Emit empty QVariant on error
    }
    catch (...) {
        qCritical() << "Unknown exception in executeTask!";
        emit resultBackgroundTask(QVariant());  // Emit empty QVariant on unknown error
    }
}





