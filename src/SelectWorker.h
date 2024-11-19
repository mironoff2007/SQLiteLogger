#ifndef SELECTWORKER_H
#define SELECTWORKER_H


#include <QObject>
#include <QThread>
#include "abstractWorker.h"
#include "abstractWorker.cpp"


class SelectWorker: public AbstractWorker
{
public:
    SelectWorker();
    QVariant getResult() override;

};
#endif // SELECTWORKER_H

