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
    connect(m_backgroundWorker, &AbstractBackgroundWorker::resultTask, this, &AbstractWorker::resultOnMain, Qt::QueuedConnection);

    m_thread->start();
}

void AbstractWorker::resultOnMain(const QVariant &result)
{
    emit resultTask(result);
}


void AbstractBackgroundWorker::runTaskOnBackGround(const QVariant &param) {
    try {
        const QVariant result = this->exequteTask(param);

        // Safely check if the result is a QStringList
        if (result.canConvert<QStringList>()) {
            QStringList retrievedList = result.value<QStringList>();
            qDebug() << "runTaskOnBackground - List size:" << retrievedList.size();
            emit resultTask(result);  // Success: emit the result
        } else {
            qWarning() << "Error: Result is not a QStringList!";
            emit resultTask(QVariant());  // Emit empty QVariant on failure
        }
    }
    catch (const std::exception &e) {
        qCritical() << "Exception in executeTask:" << e.what();
        emit resultTask(QVariant());  // Emit empty QVariant on error
    }
    catch (...) {
        qCritical() << "Unknown exception in executeTask!";
        emit resultTask(QVariant());  // Emit empty QVariant on unknown error
    }
}





