#include "AbstractWorkerTemp.h"


AbstractWorkerTemp::AbstractWorkerTemp(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
{
    auto worker = new BackGroundWorker;
    worker->moveToThread(m_thread.data());

   // connect(this, &AbstractWorkerTemp::onMainCall, worker, &BackGroundWorker::runTaskOnBackGround, Qt::QueuedConnection);
   // connect(worker, &BackGroundWorker::resultTask, this, &AbstractWorkerTemp::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}






