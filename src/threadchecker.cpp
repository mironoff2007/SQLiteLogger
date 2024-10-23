#include "threadchecker.h"
#include <QThread>
#include <QObject>
#include <QCoreApplication>
#include <QDebug>

void ThreadChecker::logIfMainThread(QString tag) {
    const bool isGuiThread = QThread::currentThread() == QCoreApplication::instance()->thread();
    const QString isGuiThreadStr = isGuiThread ? "true" : "false";
    qDebug() << tag + ":isGuiThread-" + isGuiThreadStr;
}

