#ifndef SELECTWORKER_H
#define SELECTWORKER_H


#include <QObject>
#include <QThread>
#include "abstractWorker.h"
#include "abstractWorker.cpp"


class SelectWorker: AbstractTask
{

    explicit SelectWorker();

};
#endif // SELECTWORKER_H

