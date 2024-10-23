#ifndef THREADCHECKER_H
#define THREADCHECKER_H
#include <QString>
#include <string>


class ThreadChecker
{
public:
    ThreadChecker();

public:
    static void logIfMainThread(const QString tag);

};

#endif // THREADCHECKER_H
