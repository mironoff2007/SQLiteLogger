#ifndef ABSTRACTBACKGROUNDWORKER_H
#define ABSTRACTBACKGROUNDWORKER_H

#include <QObject>


class AbstractBackGroundWorker : public QObject
{
    Q_OBJECT


signals:
    virtual void resultTask(const QVariant &param) = 0;

public slots:
    virtual void runTaskOnBackGround() = 0;

};

#endif
