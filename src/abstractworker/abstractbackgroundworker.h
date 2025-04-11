#ifndef ABSTRACTBACKGROUNDWORKER_H
#define ABSTRACTBACKGROUNDWORKER_H

#include <QObject>
#include "abstractWorker.h"


class AbstractBackgroundWorker : public QObject
{
    Q_OBJECT
public:
     explicit AbstractBackgroundWorker(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void resultTask(const QVariant &result);

public slots:
    void runTaskOnBackGround(const QVariant &param);


public:
    virtual const QVariant executeTask(const QVariant &param)= 0;

};
#endif // ABSTRACTBACKGROUNDWORKER_H
