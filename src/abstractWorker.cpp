#include "abstractWorker.h"
#include <QDebug>

AbstractWorker::AbstractWorker(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
{
    auto worker = new AbstractBackGroundWorker;
    worker->moveToThread(m_thread.data());

    connect(this, &AbstractWorker::startTask, worker, &AbstractBackGroundWorker::runTaskOnBackGround, Qt::QueuedConnection);
    //connect(worker, &BackGroundWorker::resultTask, this, &arraystack::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}

AbstractBackGroundWorker::AbstractBackGroundWorker(QObject *parent): QObject(parent)
{

}


void AbstractBackGroundWorker::runTaskOnBackGround()
{

    QStringList list;
    //emit resultSelectFileNames(list);
}



