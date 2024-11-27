#ifndef SELECTWORKER_H
#define SELECTWORKER_H


#include <QObject>
#include <QThread>
#include "abstractWorker.h"
#include "abstractWorker.cpp"


class SelectWorker: AbstractBackGroundWorker
{

    explicit SelectWorker();

};
#endif // SELECTWORKER_H

