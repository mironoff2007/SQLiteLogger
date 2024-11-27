#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>

class AbstractTask;
class AbstractTask : public QObject
{
    Q_OBJECT


public:
    virtual QVariant& exequteTask(const QVariant &param)= 0;

};

#endif
