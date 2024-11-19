#include "AbstractWorker.h"

AbstractWorker::AbstractWorker(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
{

}


AbstractWorker::~AbstractWorker()
{
    m_thread->quit();
    m_thread->wait();
}
/*


void AbstractWorker::onMainMethodCall()
{
    emit onMainCall();//signal
}

void BackGroundWorker::handleSelectFileNames()
{
    QStringList list;
    emit resultSelectFileNames(list);
}
*/

